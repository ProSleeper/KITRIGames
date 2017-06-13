using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Starter : MonoBehaviour
 {

	// Use this for initialization
	void Start ()
	{
		GameObject go = new GameObject();
		go.AddComponent<GameManager>();
		go.name = "GameManager";

		// 신이 변경 되어도 삭제 안함
		DontDestroyOnLoad(go);
	}

}
