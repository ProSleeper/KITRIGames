using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class UIManager : MonoSingleton<UIManager>
{
	GameObject DamagePrefab = null;

	public override void Init()
	{
		// base.Init(); -> DontDestroyOnLoad()
	}

	private void Awake()
	{
		DamagePrefab = Resources.Load("UI/DamageText")
			as GameObject;
		if(DamagePrefab == null)
		{
			Debug.Log("제발 UI/ DamageText 있나 확인먼저 하세요");
			return;
		}
	}

	public void CreateDamageText(string text, float showTime)
	{
		GameObject go = Instantiate(
			DamagePrefab, this.transform);

		go.transform.localPosition = Vector3.zero;
		go.transform.localScale = Vector3.one;

		DamageText dt = go.GetComponent<DamageText>();
		dt.Set(text, showTime);
	}

}
