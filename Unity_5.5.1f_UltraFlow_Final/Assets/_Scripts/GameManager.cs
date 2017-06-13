using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public enum StageScene
{
	None,
	Stage_01,
	Max
}

public class GameManager : MonoBehaviour
 {
	StageScene CurStage = StageScene.None;

	void Start ()
	{
		// 4.X 5.X 초반
		// Application.LoadLevel(0);
		//
		// SceneManager.LoadScene()
	}
	
	void Update ()
	{
		// Backspave -> 안드로이드 취소키
		if (Input.GetKeyDown(KeyCode.Backspace))
		{
			CurStage++;
			if (CurStage >= StageScene.Max)
			{
				CurStage = StageScene.Max;
				return;
			}		

			SceneManager.LoadScene(
				CurStage.ToString());
		}
	}
}
