using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameManager : MonoSingleton<GameManager>
{

	void Start ()
	{
		GameObject Player = GameObject.Find("Player");
		Actor playerScripts = Player.GetComponent<Actor>();
		CameraManager.Instance.CameraInit(playerScripts);
	}
	
	void Update ()
	{
		
	}
}
