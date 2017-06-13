using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public enum AniState
{
	None,
	Idle,
	Walk,
	Attack,
	Damage,
	Dead,
}

public delegate void EndEvent();

public class AnimationCtrl : MonoBehaviour
{
	EndEvent End = null;
	AniState CurState = AniState.None;
	Animation Anim = null;

	public AniState State
	{
		get
		{
			return CurState;
		}
	}

	public void Set(EndEvent _endEvent)
	{
		End = _endEvent;
		Anim = this.GetComponent<Animation>();
		if(Anim == null)
		{
			Debug.Log("Not Found Animation in " 
				+ gameObject.name);
			return;
		}
	}

	public void AnimationEndEvent()
	{
		if (End != null)
			End();
	}

	public void Play(AniState _state, bool bforce = false)
	{
		// Player -> false
		// Enemy -> true
		if (bforce == true)
		{ 
			Anim.Stop();
		}
		else if (CurState == _state)
			return;

		CurState = _state;
		Anim.Play(CurState.ToString());
	}


}
