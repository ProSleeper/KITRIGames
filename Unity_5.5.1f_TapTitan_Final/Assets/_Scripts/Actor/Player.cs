using System.Collections;
using System.Collections.Generic;
using UnityEngine;


public class Player : MonoBehaviour
{
	AnimationCtrl AniCtrl = null;

	int Level = 9;
	// 기본 능력치
	StatusTemplate PlayerTemplate = null;
	// 기본 능력치 + 알파( 아이템 스킬 버프 ... )
	CharacterStatus Status = new CharacterStatus();

	void Start ()
	{
		AniCtrl = 
			this.GetComponentInChildren<AnimationCtrl>();
		AniCtrl.Set(EndAnimtion);

		SetAnimtion(AniState.Idle);

		PlayerTemplate = 
			StatusManager.Instance.Get(Level.ToString());
		Status.AddStatusData(ConstValue.PlayerStatusKey,
			PlayerTemplate.STATUS_DATA);

		// 아이템 소지
		ItemTemplate item = ItemManager.Instance.Get("1");
		Status.AddStatusData("Item_Weapon", item.STATUS_DATA);

		Debug.Log(item.NAME + "착용시 공격력 : " 
			+ Status.GetStatusData(eStatusData.Attack));

		Status.RemoveStatusData("Item_Weapon");

		Debug.Log(item.NAME + "해지시 공격력 : "
			+ Status.GetStatusData(eStatusData.Attack));

		// Status.RemoveStatusData(ConstValue.PlayerStatusKey);
	}

	public int CalculateDamage()
	{
		double calDamage = 
			Status.GetStatusData(eStatusData.Attack);

		int p = Random.Range(0, 100);

		if (p <= 
			(Status.GetStatusData(eStatusData.CriticalPercent) * 100))
		{
			// Critical
			calDamage += (int)(calDamage *
			Status.GetStatusData(eStatusData.CriticalDamage));
		}

		return (int)calDamage;
	}

	public bool Attack()
	{
		SetAnimtion(AniState.Attack);
		return true;
	}


	void EndAnimtion()
	{
		switch (AniCtrl.State)
		{
			case AniState.Attack:
				SetAnimtion(AniState.Idle);
				break;
		}
	}

	void SetAnimtion(AniState state)
	{
		AniCtrl.Play(state);
	}
}
