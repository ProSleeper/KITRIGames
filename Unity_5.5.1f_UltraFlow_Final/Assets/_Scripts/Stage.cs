using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Stage : MonoBehaviour
{
    GameObject OriginBall = null;
	GameObject OriginBoard = null;

	BounceBall PlayBall = null;
    GoalObject Goal = null;

    public int BallCollCount = 3;

	void Start ()
    {
        OriginBall =
            Resources.Load("Prefabs/BounceBall")
            as GameObject;

		OriginBoard =
			Resources.Load("Prefabs/UI/Count_Board")
			as GameObject;

		if (OriginBall == null || OriginBoard == null)
        {
            Debug.Log("BounceBall or OriginBoard is Load Failed!");
            return;
        }

        GameObject temp =
            GameObject.FindGameObjectWithTag("Goal");
        Goal = temp.GetComponent<GoalObject>();

        ReCreate();
    }

    void ReCreate()
    {
        if(PlayBall != null)
        {
            Destroy(PlayBall.gameObject);
        }

        GameObject temp =
           Instantiate(OriginBall, this.transform);
        temp.transform.position =
            new Vector2(0, -4);
        PlayBall = temp.GetComponent<BounceBall>();

		//--------------------------------------------------
		temp = Instantiate(OriginBoard);
		// Parent 설정
		CountBoard cb = temp.GetComponent<CountBoard>();
		cb.TargetTrans = PlayBall.transform;
		//--------------------------------------------------

		PlayBall.Init(this, BallCollCount,
			cb.SetText, cb); // .SelfRemove);
    }

    public void IsGameOver(bool isSuccess = false)
    {
        if(isSuccess == true)
        {
            Debug.Log("Success");
        }
        else
        {
            Debug.Log("Fail");
        }
    }
    
}
