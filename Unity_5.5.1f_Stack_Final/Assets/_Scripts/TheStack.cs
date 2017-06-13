using System.Collections;
using System.Collections.Generic;
using UnityEngine;

//코드 보면서 느낌점
//되게 간단한 코드이지만 꽤나 잘 적용되어있는 하나의 함수는 하나의 목적을 가진다 라는게 잘 정의 되었다고 생각듬
//나는 this나 getcomponent로 많이 쓰는데 이제부터 2번이상 그 변수를 쓰는 경우는 꼭 다른 변수에 저장해서 쓰자
//c++이라면 #define이라고 할 수 있는 상수값들 정의도 꽤 잘되어있음. 나도 적극 활용!

public class TheStack : MonoBehaviour
{
    // Const Value
    private const float BOUND_SIZE = 3.5f;          // 블럭 사이즈 초기값
    private const float MOVING_BOUNDS_SIZE = 3f;    // 블럭 이동반경 사이지
    private const float STACK_MOVING_SPEED = 5.0f;  // 스택 오브젝트 이동 속도
    private const float BLOCK_MOVING_SPEED = 3.5f;  // 블럭 이동 속도
    private const float ERROR_MARGIN = 0.1f;        // 오차 범위

    private const string BEST_SCORE_KEY = "BestScore";
    private const string BEST_COMBO_KEY = "BestCombo";

    //복사해서 계속 사용할 블럭
    public GameObject OriginBlock = null;

    //크기와 위치를 검사할 이전 블럭
    private Vector3 PrevBlockPosition;

    //아마도 다음 생성할 블럭?
    private Vector3 DesiredPosition;

    //블럭 사이즈 (블럭은 기본적으로 3.5, 3.5의 크기이다)
    private Vector2 StackBounds
        = new Vector2(BOUND_SIZE, BOUND_SIZE);

    Transform LastBlock = null;

    //스택 카운트 -1부터 시작이니 한개 쌓는 순간 9이 된다.
    int StackCount = -1;

    //X와 Z 두가지 방향을 검사할 플래그
    bool IsMovingX = true;

    //블럭의 움직임을 담당할 변수
    float BlockTransition = 0f;

    float SecondaryPosition = 0f;

    int ComboCount = 0;
    int MaxCombo = 0;

    int BestScore = 0;
    int BestCombo = 0;

    public Color PrevColor;
    public Color NextColor;

    //게임오버 판정
    bool IsGameOver = true;


    private void Start()
    {
        // 화면 비율 설정(9/16) 가로는 9 세로는 16으로 맞춰준것이다.
        Screen.SetResolution(Screen.width * 9 / 16, Screen.width, true);

        //블럭이 잘 로드 됐는지 예외처리
        if (OriginBlock == null)
        {
            Debug.Log("OriginBlock is NULL");
            return;
        }

        //데이터 기본 저장
        BestScore = PlayerPrefs.GetInt(BEST_SCORE_KEY, 0);
        BestCombo = PlayerPrefs.GetInt(BEST_COMBO_KEY, 0);


        //처음 색을 랜덤하게 줌
        PrevColor = GetRandomColor();
        NextColor = GetRandomColor();

        //이전 블럭의 초기 위치는 0,-1, 0
        PrevBlockPosition = Vector3.down;
        Spawn_Block();
        //Spawn_Block();

        ////TheStack Stack =
        ////    GameObject.Find("TheStack").GetComponent<TheStack>();

        ////A
        ////    B
        ////        D
        ////    C

        //// B
        //transform.FindChild("B");
        //transform.GetChild(0);
        //// D
        //transform.FindChild("B/D");
        //transform.GetChild(0).GetChild(0);
    }

    private void Update()
    {

        if (IsGameOver == true)
        {
            if (Input.GetKeyDown(KeyCode.R)
                || Input.touchCount > 2
                )
                Restart();
            return;
        }

        // 마우스 왼쪽 클릭 , 스마트폰 터치
        if (Input.GetMouseButtonDown(0))
        {
            //Spawn_Block();

            if (PlaceBlock() == true)
            {
                Spawn_Block();
            }
            else
            {
                // 게임 오버
                IsGameOver = true;
                EndEffect();
                CheckScore();
                Debug.Log("GameOver");
                UIManager.Instance.SetScore(
                    BestScore, BestCombo, StackCount, MaxCombo);
            }

        }

        MoveBlock();

        transform.position =
            Vector3.Lerp(transform.position,
            DesiredPosition,
            STACK_MOVING_SPEED * Time.deltaTime);
    }

    bool Spawn_Block()
    {
        Debug.Log("블럭생성");
        //이전블럭 저장
        //맨 처음에는 LastBlock이 Null이기 때문에 해당 작업을 실행하지 않음 
        if (LastBlock != null)
            PrevBlockPosition = LastBlock.localPosition;



        // gameObject   // GameObject
        // transform    // Transform


        GameObject newBlock = null;
        Transform newTrans = null;

        //새로운 블럭 생성
        newBlock = Instantiate(OriginBlock);

        //잘 생성 됐는지 예외처리
        if (newBlock == null)
        {
            Debug.Log("NewBlock Instantiate Failed!");
            return false;
        }

        //생성된 블럭 색 변경
        ColorChange(newBlock);

        //새로 생성된 블럭의 Transform 값 저장
        newTrans = newBlock.transform;

        //이 스크립트를 가지고 있는 오브젝트를 부모로 해줌
        newTrans.parent = this.transform;

        //새로 생성된 블럭의 위치를 이전 블럭위치에서 y값으로 1만 올려줌
        //맨 처음의 경우 0,-1,0이므로 새로운 포지션은 0,0,0이 된다.
        newTrans.localPosition = PrevBlockPosition + Vector3.up;

        //회전값 초기화
        newTrans.localRotation = Quaternion.identity;

        //크기는 StackBound의 크기로 맞춰 줌
        //맨 처음에는 StackBound의 크기가 3.5, 3.5 이다.
        newTrans.localScale = new Vector3(StackBounds.x, 1, StackBounds.y);

        // // Test Code
        // StackBounds *= 0.95f;

        //새로 생성했으니 카운트 +1
        StackCount++;
        //Debug.Log(StackCount);

        //변수명을 직역하자면 원하는위치..정도? 여튼 스택은 계속 쌓일테고 우리는 항상 일정한 위치를 유지해야하기 때문에
        //StackCount * 0,-1,0 해주면 현재 쌓여 있는 스택만큼 아래로 내려가는 위치가 나온다.
        //Update에서 이 DesiredPosition을 이용해서 위치를 잡아준다.
        DesiredPosition = Vector3.down * StackCount;

        //X축 한번 Z축 한번을 번갈아서 나오기 때문에 계속해서 바꿔줌 
        IsMovingX = !IsMovingX;

        //움직임 멈춤?
        BlockTransition = 0f;

        //생성된 블럭을 움직일 마지막 블럭으로 해줌
        LastBlock = newTrans;

        //콤보와 점수 계산
        UIManager.Instance.SetScore(StackCount, ComboCount);

        return true;
    }

    //새로운 블럭을 생성시킨 후 움직임을 담당하는 함수
    void MoveBlock()
    {
        //정해놓은 속도에 deltatime을 곱해줌(의미는 어떠한 환경에서도 느리면 느린만큼 빠르면 빠른만큼 1초마다 해당 속도만큼 이동하겠다는 것)
        BlockTransition += Time.deltaTime * BLOCK_MOVING_SPEED;
       // Debug.Log(BlockTransition);
        //약간 설명하기 어려운데 위의 blocktransition이 계속해서 증가한다.
        //그리고 증가하다가 최대값이 BOUND_SIZE가 되면 다시 내려간다..
        
        //      BOUND_SIZE 
        //          /\        /\        /\
        //         /  \      /  \      /  \
        //        /    \    /    \    /    \
        //       /      \  /      \  /      \
        //      /        \/        \/        \
        //     0         1         2         3
        //위의 그림이 mathf.pingpong의 주기 그림
        //숫자 부분이 blocktransition의 값 blocktransition은 그냥 계속 증가하기만 할뿐이다.
        //하지만 핑퐁 내부적으로는 blocktransiotion값을 계속해서 바꿔나가는 것이다.

        //sin도 동일한 위치만큼 이동하지만 이동하는 방식? 트윈이 다르다.
        //핑퐁은 0부터 2번쨰 인자값을 최대로 이동하기 때문에 우리는 나오는 값에서 절반만큼 뺴주어서 
        //좌표 0을 기준으로 왔다갔다 거리게 만든다. 이게 아니면 핑퐁은 0까지 갔다가 다시 BOUND_SIZE로 이동함
        //-BOUND_SIZE/2를 없애고 실행해보면 뭔지 알게 됨.
        // float movePosition = Mathf.Sin(BlockTransition) * BOUND_SIZE;
        float movePosition = Mathf.PingPong(BlockTransition, BOUND_SIZE) - BOUND_SIZE / 2;


        //x축 이동
        if (IsMovingX)
        {
            // origin
            //LastBlock.localPosition =
            //    new Vector3(movePosition * MOVING_BOUNDS_SIZE,
            //    StackCount, 0);
            // fixed
            
            //블럭의 위치 이동
            //위에서 구한 movePosition은 BOUND_SIZE가 최대 블록 크기이기 때문에 movePosition만 //넣어준다면 움직이는 블럭은 딱 -3.5 ~ 3.5까지만 움직인다. 이렇게 움직여도 상관없는데 실제로 게임을
            //해보면 굉장히 좁은 움직임으로 느껴진다. 그래서 MOVING_BOUNDS_SIZE를 곱해주면 곱해준 만큼
            //더 넓게 움직인다. 현재는 3배 즉 -10.5 ~ 10.5까지 움직인다.
            //y값은 블럭 하나가 쌓일때마다 1씩 증가하므로 StackCount로 하고
            //Z값은 이전에 블럭을 검사했을때 변경됐다면 블럭을 검사한 코드에서 SecondaryPosition을 변경했고
            //변경한 값으로 맞춰줘야 하기 때문에 SecondaryPosition으로 해줌
            LastBlock.localPosition =
                new Vector3(movePosition * MOVING_BOUNDS_SIZE,
                StackCount, SecondaryPosition);
        }
        //z축 이동
        else
        {
            // origin
            //LastBlock.localPosition =
            //    new Vector3(0,
            //    StackCount, -movePosition * MOVING_BOUNDS_SIZE);
            // fixed
            //X축으로 움직일때와 x와z만 바뀌고 x는 화면으로 오는 방향이 +이고 z는 -이기 때문에
            //movePosition에 -를 해줌
            LastBlock.localPosition =
                new Vector3(SecondaryPosition,
                StackCount, -movePosition * MOVING_BOUNDS_SIZE);
        }

    }

    //이전 블럭과의 위치, 크기 체크
    bool PlaceBlock()
    {
        //이전 블럭의 위치 저장
        Vector3 lastPosition = LastBlock.transform.localPosition;

        //IsMovingX을 체크해서 true라면 x방향으로 움직이는 중
        if (IsMovingX)
        {
            //x축으로 움직이기 때문에 lastposition(현재 움직이는 블럭)과 prevblockposition(바로 아래 이전 블럭)의 x축의 위치값을 계산해서 저장
            float deltaX = PrevBlockPosition.x - lastPosition.x;

            //이건 x축을 계산할때 현재 움직이는 블럭의 위치가 이전 블럭의 왼쪽인지 오른쪽인지 혹은 x위치가 큰지 작은지를 판별해서
            //어느쪽으로 이동시킬지(실제 게임에서는 자르는 것으로 느껴지겠지만 구현상에선 어느쪽이든 동일하게 축소시키고 해당 방향으로 위치를 이동시켜서 자르는 것으로 구현함)
            bool isNegativeNum = (deltaX < 0) ? true : false;

            //위에서 구한 위치의 절대값..(개인적으로는 이 값으로 바로 방향을 판단할 수 있겠지만 isNegativeNum라는 변수를 주는게 이 밑의 구현에서 더 깔끔할듯)
            deltaX = Mathf.Abs(deltaX);

            //설정한 ERROR_MARGIN보다 더 크게 위치가 어긋났다면
            if (deltaX > ERROR_MARGIN)
            {
                //콤보실패
                ComboCount = 0;
                // 벗어난 만큼 x값을 빼서 다음 만들 블럭의 크기를 줄인다.
                //그리고 줄인 값이 0이하라면 게임오버
                StackBounds.x -= deltaX;
                if (StackBounds.x <= 0)
                {
                    // 게임오버
                    return false;
                }

                //(아직 축소 전) 먼저 축소시키고 자리잡을 위치를 구한다.
                float middle = (PrevBlockPosition.x + lastPosition.x) / 2;
                //현재 움직이는 블럭의 크기를 위에서 StackBounds.x를 줄인 값으로 변경
                LastBlock.localScale = new Vector3(StackBounds.x, 1, StackBounds.y);

                //간단하게 말해서, 현재 블럭의 X위치를 위에서 구한 middle(축소시킨 후 자리 잡을 위치)로 옮긴다
                //사실 아래 코드처럼 안하고 lastblock.localposition = new vector3
                //middle, lastblock.localposition.y, lastblock.localposition.z)도 됨
                //근데 쓰고 보니 이거나 밑에 거나.. 그게 그거인듯
                //주석 쓰다보니 그대로 쓸 수 있는 코드들이 많이 보이기는 하는데 변수에 따로 담아서 사용하는게 많다
                //어느게 좋다고 말은 못하고 단지 내가 쓴 코드가 아니라서 변수에 담아서 쓰는게 보기 쉽고 
                //좀 더 깔끔해 보이기는 하는듯.. 한마디로 변수에 담아서 쓰는게 더 좋은듯 ㅋㅋ
                Vector3 tempPosition = LastBlock.localPosition;
                tempPosition.x = middle; 
                //placeblock함수를 실행할때 lastposition에 현재 움직이는 블럭의 위치를 저장했는데,
                //여기서 다시 저장하는 이유는, 시작할때 함수 제일 처음에 저장한건 블럭을 정확하게 일치 시켰을때의
                //상황을 생각해 담은것이고 현재 저장하는 이유는 블럭의 위치가 변했으니 변한 위치를 다시 저장하는것
                LastBlock.localPosition = lastPosition = tempPosition;

                //변수 이름대로 현재 블럭의 잘라낼 부분을 생성해야하는데 그 크기로 쓸 값
                float rubbleHalfScale = deltaX / 2;

                //파편 블럭 생성
                //매개변수인자의 첫번쨰는 생성될 위치, 두번째는 생성될 크기
                //위에서 판별한 isNegativeNum으로(true라면 현재 블럭이 x축으로 더 +된 방향에 있는 것이고
                // false라면 현재 블럭이 x축으로 더 -된 쪽에 있는 것이다.)
                //그래서 +방향에 있다면 +방향으로 파편이 생겨야하고 -방향이면 -방향으로 파편이 생겨야한다.
                //이전 블럭의 위치가 0 크기가 1, 현재 블럭의 위치가 위치가 0.5 크기가 1 이라면
                //위에서 계산한 lastposition.x는 0.25가 되고 stackbounds는 0.5가 되고 
                //rubblehalfscale은 0.25가 된다. 그러므로 0.25 + 0.5/2 + 0.25 가 되면 생성할
                //파편의 위치는 0.75가 되고 크기는 0.5가 된다.
                CreateRubble(new Vector3(
                    isNegativeNum
                    ? lastPosition.x + StackBounds.x / 2 + rubbleHalfScale
                    : lastPosition.x - StackBounds.x / 2 - rubbleHalfScale
                    , lastPosition.y
                    , lastPosition.z),
                    new Vector3(deltaX, 1, StackBounds.y)
                    );
            }
            //어긋난 값이 설정한 ERROR_MARGIN보다 작다면
            else
            {
                // 현재 움직이는 블럭의 위치를 이전 블럭의 위치에서 y값만 1 올리고 맞춰줌
                LastBlock.localPosition =
                    PrevBlockPosition + Vector3.up;
                //콤보증가
                ComboCheck();
            }
        }
        //IsMovingX을 체크해서 true라면 z방향으로 움직이는 중        
        else
        {
            //아래 구현은 위에 x축 구현과 값만 다를 뿐 동일함
            //조금만 생각하면 매개변수로 몇몇 값 주면 함수로 빼서 중복코드 줄일 수 있을듯
            float deltaZ = PrevBlockPosition.z - lastPosition.z;
            bool isNegativeNum = (deltaZ < 0) ? true : false;
            deltaZ = Mathf.Abs(deltaZ);
            if (deltaZ > ERROR_MARGIN)
            {
                ComboCount = 0;
                StackBounds.y -= deltaZ;
                if (StackBounds.y <= 0)
                {
                    return false;
                }

                float middle = (PrevBlockPosition.z +
                    lastPosition.z) / 2;
                LastBlock.localScale = new Vector3(StackBounds.x,
                    1, StackBounds.y);

                Vector3 tempPosition = LastBlock.localPosition;
                tempPosition.z = middle;
                LastBlock.localPosition = lastPosition = tempPosition;

                float rubbleHalfScale = deltaZ / 2;
                CreateRubble(
                    new Vector3(
                      lastPosition.x
                    , lastPosition.y
                    , isNegativeNum
                    ? lastPosition.z + StackBounds.y / 2 + rubbleHalfScale
                    : lastPosition.z - StackBounds.y / 2 - rubbleHalfScale),
                    new Vector3(StackBounds.x, 1, deltaZ)
                    );
            }
            else
            {
                LastBlock.localPosition =
                    PrevBlockPosition + Vector3.up;
                ComboCheck();
            }
        }

        //현재 블럭의 움직이 x였으면 x위치 저장 z면 z저장.. 인데 이걸로 다음 나올 블럭의 해당 위치를 구하는듯
       SecondaryPosition =
            (IsMovingX) ? LastBlock.localPosition.x :
            LastBlock.localPosition.z;

        return true;
    }

    //잘라진 파편 생성함수
    void CreateRubble(Vector3 pos, Vector3 scale)
    {
        //블럭의 색상을 동일하게 하기 위해서 현재 블럭의 복사본으로 생성
        GameObject go = Instantiate(LastBlock.gameObject);
        //이 스크립트를 가지고 있는 게임오브젝트를 부모로 설정
        go.transform.parent = this.transform;

        //매개변수로 받은 위치로 변경
        go.transform.localPosition = pos;
        //매개변수로 받은 크기로 변경
        go.transform.localScale = scale;
        //회전 초기화
        go.transform.localRotation = Quaternion.identity;

        //Rigidbody rigid =
        //리지드바디를 주는 이유는 알아서 떨어지게 중력을 주기 위함.
        go.AddComponent<Rigidbody>();
        //// test code
        //rigid.AddForce(
        //    new Vector3(
        //        Random.Range(100, 300),
        //        Random.Range(500, 700),
        //        Random.Range(100, 300)
        //        )
        //    );

        //이름은 Rubble로 만듬
        go.name = "Rubble";
    }

    //블럭을 잘 맞췄을시 콤보 체크
    void ComboCheck()
    {
        //콤보증가시키고
        ComboCount++;

        //현재 콤보가 이전 최대 콤보보다 크면 최대콤보 교체
        if (MaxCombo < ComboCount)
            MaxCombo = ComboCount;

        //5콤보를 할때마다 블럭의 크기를 증가시킴
        //개인적인 얘기로 현재구현은 새로 나오는 블럭의 크기만 증가하게 되어있음
        //원래 게임은 현재 블럭과 새로나오는 블럭 모두 크기가 증가한다.
        //간단하게 증가 시킬 수 있는데 그러면 위치가 어긋나는 버그가 생긴다. 해당부분도 맞춰줘야 한다.
        if ((ComboCount % 5) == 0)
        {
            Debug.Log("5Combo Success!");
            //현재 크기에서 1.2배 해줌
            StackBounds *= 1.2f;

            //정해준 BOUND_SIZE크기 이상으로 커지지않게 만듬
            StackBounds.x =
                (StackBounds.x > BOUND_SIZE) ? BOUND_SIZE : StackBounds.x;
            StackBounds.y =
                (StackBounds.y > BOUND_SIZE) ? BOUND_SIZE : StackBounds.y;
        }
    }

    Color GetRandomColor()
    {
        //랜덤칼라를 구하는건데 100~250구간인 이유는 파스텔톤을 유지하기 위함이라는.. 듯
        //칼라값을 어떻게 구하는지는 잘 모르겠다.
        //뒤에 255로 나눠주는건 실제론는 rgb값이지만 우리는 코드상에서 0~1로 취급하기 때문
        float r = Random.Range(100f, 250f) / 255f;
        float g = Random.Range(100f, 250f) / 255f;
        float b = Random.Range(100f, 250f) / 255f;

        return new Color(r, g, b);
    }

    void ColorChange(GameObject go)
    {
        //전체적인 설명
        //아래 선형보간을 이용해서 색을 조금씩 바꾼다.
        //스택카운트는 시작시 0부터 증가하기 때문에 선형보간에서 시간매개변수에 들어가는 값이
        //0.1 -> 0.2 -> 0.3 이런식으로 증가한다.(여기서 0.1은 칼라 값으로 나름 큰값, 256을 1로 바꿔서의 0.1이기 때문에 0.1이란 256색 입장에서 볼때 25.6이다.  )
        //그래서 스택카운트가 10개씩 증가할때마다 Prev와 Next의 칼라가 같아 지므로
        //아래 비교를 통해서 두개의 칼라가 같아지면 Prev에 Next를 넣고 Next는 랜덤칼라를 받아온다.
        //이런식으로 계속해서 색이 미세하게 바뀌게 된다.
        //배경은 블러과 아주 미세하게 다르게 한다.
        Color applyColor =
            Color.Lerp(
                PrevColor, NextColor,
                (StackCount % 11) / 10f);

        Renderer rn = go.GetComponent<Renderer>();

        if (rn == null)
        {
            Debug.Log("Renderer is NULL!");
            return;
        }

        rn.material.color = applyColor;
        Camera.main.backgroundColor =
            applyColor - new Color(0.1f, 0.1f, 0.1f);

        if (applyColor.Equals(NextColor) == true)
        {
            PrevColor = NextColor;
            NextColor = GetRandomColor();
        }
    }

    void EndEffect()
    {
        int childCount = this.transform.childCount;

        for (int i = 1; i < 20; i++)
        {

            if (childCount < i)
                break;

            GameObject go =
                this.transform.GetChild(childCount - i).gameObject;

            if (go.name.Equals("Rubble"))
                continue;

            Rigidbody rigid = go.AddComponent<Rigidbody>();

            rigid.AddForce(
                (Vector3.up * Random.Range(0, 10f)
                + Vector3.right * (Random.Range(0, 10f) - 5f))
                 * 100f
                );
        }
    }

    void CheckScore()
    {
        //스택의 카운트 즉 얼만큼 쌓았냐가 곧 점수
        //베스트보다 더 많이 쌓았으면 베스트점수와 베스트 콤보 모두 바꿈
        //현재 코드의 약간의 문제점은 점수와 콤보가 따로 분리해서 검사가 아니라
        //점수가 높아지면 콤보도 높아지는 이상한 상황
        //그리고 최대 점수와 콤보를 저장
        if (BestScore < StackCount)
        {
            BestScore = StackCount;
            BestCombo = MaxCombo;

            PlayerPrefs.SetInt(BEST_SCORE_KEY, BestScore);
            PlayerPrefs.SetInt(BEST_COMBO_KEY, BestCombo);
        }
    }

    //재시작을 위하여 전부 초기화 해주는 함수
    public void Restart()
    {
        //모든 블럭은 해당 스크립트를 물고 있는 오브젝트(The Stack)의 
        //하위에 있으므로 자식의 숫자를 구하면 쌓여있는 블럭의 숫자를 알 수 있다.
        int childCount = this.transform.childCount;

        //자식으로 있는 모든 블럭을 파괴
        for (int i = 0; i < childCount; i++)
        {
            Destroy(this.transform.GetChild(i).gameObject);
        }

        //게임오버 플래그 초기화
        IsGameOver = false;
        
        //현재 움직이는 블럭 null로 만듬
        LastBlock = null;
        //TheStack의 위치 초기화
        DesiredPosition = Vector3.zero;
        //블럭 사이즈 초기화
        StackBounds = new Vector2(BOUND_SIZE, BOUND_SIZE);

        //스택카운트 초기화
        StackCount = -1;
        //x방향부터 나오도록 초기화
        IsMovingX = true;
        //움직일 블럭의 주기값 초기화
        BlockTransition = 0f;
        //x와 z축을 맞춰줄 값 초기화
        SecondaryPosition = 0f;
        //콤보 초기화
        ComboCount = 0;
        //이전블럭도 초기화
        PrevBlockPosition = Vector3.down;

        //색상 재설정
        PrevColor = GetRandomColor();
        NextColor = GetRandomColor();
        
        //다시 시작하니까 블록 2개 생성
        //1개는 이전 블럭 1개는 움직일 블럭
        Spawn_Block();
        Spawn_Block();
    }
}

