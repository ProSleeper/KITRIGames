using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DamageText : MonoBehaviour
{
	UILabel Label = null;
	float ShowTime = 1.0f;
	public AnimationCurve Curve;

	float CurTime = 0.0f;
	float StartY = 0.0f;

	public float XSpeed = 300f;
	public float YSpeed = 300f;
	int IsLeft = 0;

	private void Awake()
	{
		Label = this.GetComponent<UILabel>();
	}

	public void Set(string text, float showTime)
	{
		if(Label == null)
		{
			Debug.Log("라벨이 없어요 데미지텍스트에 라벨 컴포넌트 있는지 확인하세요.");
			return;
		}

		IsLeft = Random.Range(0, 2);

		Label.text = text;
		ShowTime = showTime;

		StartY = transform.localPosition.y
			+ Random.Range(0f,100f);
		XSpeed -= Random.Range(0f, 100f);

		StartCoroutine("SetDeactive");
	}

	void Update ()
	{
		// transform.position += Vector3.up * Time.deltaTime;
		Vector3 pos = transform.localPosition;

		CurTime += Time.deltaTime;

		// 좌우
		if (IsLeft == 0)
			pos.x -= Time.deltaTime * XSpeed;
		else
			pos.x += Time.deltaTime * XSpeed;

		pos.y = StartY + Curve.Evaluate(CurTime) * YSpeed;
		
		transform.localPosition = pos;

		transform.localScale = 
			Vector3.one * Curve.Evaluate(CurTime);

	}

	IEnumerator SetDeactive()
	{
		float curTime = 0.0f;

		while(true)
		{
			curTime += Time.deltaTime;
			yield return null;
			if (curTime >= ShowTime)
				break;
		}
		Destroy(this.gameObject);
	}
}
