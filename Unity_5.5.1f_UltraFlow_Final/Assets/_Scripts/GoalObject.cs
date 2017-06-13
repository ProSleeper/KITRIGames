using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GoalObject : MonoBehaviour
{
    Transform BallTrans = null;

    private void OnTriggerEnter2D(Collider2D collision)
    {
        if(collision.gameObject.name.Contains("BounceBall"))
        {
            BallTrans = collision.transform;
            collision.GetComponent<Rigidbody2D>().velocity =
                Vector2.zero;

            GameObject.
                Find("Stage").
                GetComponent<Stage>().
                IsGameOver(true);

        }
    }

    private void Update()
    {
        if(BallTrans != null)
        {
            BallTrans.position
                = Vector2.Lerp(BallTrans.position,
                this.transform.position, 3f * Time.deltaTime);
        }
    }

}
