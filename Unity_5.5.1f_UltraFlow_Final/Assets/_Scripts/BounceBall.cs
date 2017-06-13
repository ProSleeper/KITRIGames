using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public delegate void CollEvent(int count);
// public delegate void RemoveBall();

[RequireComponent(typeof(Rigidbody2D))]
public class BounceBall : MonoBehaviour
{
	CollEvent Event = null;
	// RemoveBall RemoveEvent = null;

	CountBoard Board = null;

    bool IsButtonDown = false;
    bool BeUsed = false;

    Rigidbody2D Rigid;

    Vector2 PrevPos = Vector2.zero;
    Vector2 InputPos = Vector2.zero;

    float CurrTime = 0f;

    Stage GameStage = null;
    int CollCount = 5;

    public void Init(Stage stage, int collCnt ,
		CollEvent _event , CountBoard board) // , RemoveBall removeEvent)
    {
        GameStage = stage;
        CollCount = collCnt;
		Event = _event;
		Board = board;
		//RemoveEvent = removeEvent;

		if (Event != null)
			Event(CollCount);
	}

    private void OnCollisionEnter2D(Collision2D collision)
    {
        CollCount--;
		if(Event != null)
			Event(CollCount);

		if (CollCount < 0)
            GameStage.IsGameOver();
    }

    void Start ()
    {
        Rigid = this.GetComponent<Rigidbody2D>();
        if(Rigid == null)
        {
            Debug.Log("RigidBody2D is NULL");
            return;
        }

	}

    void Update()
    {
        if (BeUsed == false && Input.GetMouseButtonDown(0))
        {
            Vector2 pos =
                Camera.main.ScreenToWorldPoint(Input.mousePosition);

            RaycastHit2D hit;
            hit = Physics2D.Raycast(pos, Vector2.zero);

            // // 3D 
            // Ray ray = new Ray(pos, Vector3.forward);
            // RaycastHit hit3D;
            // Physics.Raycast(ray, out hit3D);

            if (hit.collider != null &&
                hit.collider.gameObject == this.gameObject)
            {
                IsButtonDown = true;
                Rigid.velocity = Vector2.zero;
                PrevPos = pos;

                // Courutine
                // StartCoroutine(CachingPos());
                // StartCoroutine("CachingPos");

                // Invoke
                // Invoke("InvokeCachingPos", 0.1f);
                // InvokeRepeating("InvokeCachingPos", 0f, 0.1f);
                // CancelInvoke("InvokeCachingPos");
            }
        }

        if (IsButtonDown == true)
        {
            InputPos = Camera.main.ScreenToWorldPoint(Input.mousePosition);
            transform.position = InputPos;

            // DeltaTime
            CurrTime += Time.deltaTime;
            if (CurrTime > 0.1f)
            {
                CurrTime = 0f;
                PrevPos = transform.position;
            }

            //if (Input.GetMouseButtonUp(0))
            //{
            //    IsButtonDown = false;
            //    Rigid.AddForce((InputPos - PrevPos) * 100f);

            //    CurrTime = 0f;
            //    PrevPos = Vector2.zero;
            //}
        }
    }

    IEnumerator CachingPos()
    {
        //Debug.Log("Test");
        //yield return null;
        while (IsButtonDown)
        {
            PrevPos = transform.position;

            //           yield return null;
            yield return new WaitForSeconds(0.1f);
        }
    }

    void InvokeCachingPos()
    {
        PrevPos = transform.position;
    }


    private void OnTriggerEnter2D(Collider2D collision)
    {
        if (IsButtonDown == true &&
            collision.gameObject.name.Equals("TriggerBlock"))
        {
            // StopCoroutine("CachingPos");

            BeUsed = true;
            IsButtonDown = false;

            Vector2 dir = (InputPos - PrevPos);

            Rigid.AddForce( dir.normalized 
                * Vector2.Distance(InputPos,PrevPos) * 200f );

            CurrTime = 0f;
            PrevPos = Vector2.zero;
        }
    }

	private void OnDestroy()
	{
		if(Board != null)
			Destroy(Board.gameObject);

		//RemoveEvent();
	}



}
