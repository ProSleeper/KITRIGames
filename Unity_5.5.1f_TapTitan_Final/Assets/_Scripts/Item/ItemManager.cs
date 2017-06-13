using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using SimpleJSON;

public class ItemManager : MonoSingleton<ItemManager>
{
	Dictionary<string, ItemTemplate> DicItem =
		new Dictionary<string, ItemTemplate>();

	private void Awake()
	{
		TextAsset itemText = 
			Resources.Load(ConstValue.ItemDataPath) as TextAsset;

		if(itemText != null)
		{
			JSONObject rootNodeData = 
				JSON.Parse(itemText.text) as JSONObject;

			if (rootNodeData != null)
			{
				JSONObject itemNodes =
					rootNodeData[ConstValue.ItemDataKey]
					as JSONObject;

				foreach (KeyValuePair<string, JSONNode> node
					in itemNodes)
				{
					DicItem.Add(node.Key,
						new ItemTemplate(node.Key, node.Value));
				}
			}
		}
		else
		{
			Debug.Log("Path : " + ConstValue.ItemDataPath);
		}
	}

	public ItemTemplate Get(string _key)
	{
		ItemTemplate tempData = null;
		DicItem.TryGetValue(_key, out tempData);
		if (tempData == null)
		{
			Debug.Log(_key + " is not containsed key");
		}

		return tempData;
	}



}
