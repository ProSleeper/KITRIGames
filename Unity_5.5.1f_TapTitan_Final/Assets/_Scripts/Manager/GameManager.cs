using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameManager : MonoSingleton<GameManager>
{
	Player PlayerScript = null;
	Enemy EnemyScript = null;
	GameObject EnemyPrefab = null;

	void Start()
	{
		// Prefab Load
		EnemyPrefab = Resources.Load("Prefabs/Enemy")
			as GameObject;
		// Create Clone
		GameObject go = Instantiate(EnemyPrefab);
		// Get Scripts Component
		EnemyScript = go.GetComponent<Enemy>();

		PlayerScript =
			GameObject.FindObjectOfType<Player>();
	}

	void Update()
	{
		if (Input.GetMouseButtonDown(0))
		{
			// Attack Speed
			// -> return

			// Player Animation
			PlayerScript.Attack();
			int damage =
				PlayerScript.CalculateDamage();
			Debug.Log("Damage : " + damage);

			UIManager.Instance.CreateDamageText(
				damage.ToString(),
				1f);

			if (EnemyScript.GetDamage(damage) == false)
			{
				// Enemy 죽음
				EnemyScript.Dead();
				Invoke("InstantiateEnemy", 2f);

				// Player Exp ++; -> Player(LevelUP)
			}
		}


	
	}

	void InstantiateEnemy()
	{
		if (EnemyScript != null)
			Destroy(EnemyScript.gameObject);

		// Create Clone
		GameObject go = Instantiate(EnemyPrefab);
		// Get Scripts Component
		EnemyScript = go.GetComponent<Enemy>();
	}

}
