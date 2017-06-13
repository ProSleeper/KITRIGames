using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using SimpleJSON;

public class StatusManager : MonoSingleton<StatusManager>
{
	Dictionary<string, StatusTemplate> DicStatus = 
		new Dictionary<string, StatusTemplate>();

	private void Awake()
	{
		TextAsset statusText =
			Resources.Load(ConstValue.StatusDataPath)
			as TextAsset;

		if(statusText != null)
		{
			// JSON Parse :: JSON -> Data
			JSONObject rootNodeData
				 = JSON.Parse(statusText.text) 
				 as JSONObject;

			if (rootNodeData != null)
			{
				JSONObject StatusNodes =
					rootNodeData[ConstValue.StatusDataKey]
					as JSONObject;

				/*
				 List<GameObject> list;
				 foreach(GameObjec temp in list)
					temp -> list[0 ~ count] 
				 */

				foreach(KeyValuePair<string,JSONNode> node 
					in StatusNodes)
				{
					DicStatus.Add(
						node.Key,
						new StatusTemplate(node.Key,
									node.Value)
					);
				}

				Debug.Log(DicStatus.Count);
			}

		}
		else
		{
			// null case
			Debug.Log("Path : " 
				+ ConstValue.StatusDataPath
				+ " is Not Founded!");
		}

	}


	public StatusTemplate Get(string _key)	
	{
		// #1
		//if (DicStatus.ContainsKey(_key) == true)
		//{
		//	StatusData tempData = null;
		//	tempData = DicStatus[_key];
		//}
		//else
		//{
		//	Debug.Log(_key + " is not containsed key");
		//}
		//return null;

		// #2
		StatusTemplate tempData = null;
		DicStatus.TryGetValue(_key, out tempData);
		// out :: C++ ref 참조를 넘김

		if (tempData == null)
		{
			Debug.Log(_key + " is not containsed key");
		}

		return tempData;
	}


}
