using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Enemy : MonoBehaviour
{
	int CurHP = 0;
	public int MaxHP = 100;

	public int HP
	{
		get
		{
			return CurHP;
		}
		set
		{
			// HP -= _damage;
			// CurHP = value;

			CurHP += value;
			if (CurHP > MaxHP)
				CurHP = MaxHP;
		}
	}

	AnimationCtrl AniCtrl = null;
	
	void Start ()
	{
		HP = MaxHP; // CurHP = MaxHP;
		AniCtrl =
			this.GetComponentInChildren<AnimationCtrl>();
		AniCtrl.Set(EndAnimation);

		AniCtrl.Play(AniState.Idle);
	}

	void EndAnimation()
	{
		switch(AniCtrl.State)
		{
			case AniState.Damage:
				AniCtrl.Play(AniState.Idle);
				break;
		}
	}

	public bool GetDamage(int _damage)
	{
		// 죽는 에니메이션 중에는 데미지 X
		if (AniCtrl.State == AniState.Dead)
			return true;

		AniCtrl.Play(AniState.Damage, true);

		HP = -(_damage);

		if (HP <= 0)
			return false;

		return true;
	}

	public void Dead()
	{
		AniCtrl.Play(AniState.Dead, true);
	}

}
