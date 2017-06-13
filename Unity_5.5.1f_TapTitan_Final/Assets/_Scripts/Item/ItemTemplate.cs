using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using SimpleJSON;

public class ItemTemplate 
{
	string StrKey = string.Empty;
	StatusData StatusData = new StatusData();
	string Name		= string.Empty;
	string Image	= string.Empty;
	string Category = string.Empty;

	public string KEY { get { return StrKey; } }
	public string NAME { get { return Name; } }
	public string IMAGE { get { return Image; } }
	public string CATEGORY { get { return Category; } }

	public StatusData STATUS_DATA { get { return StatusData; } }

	public ItemTemplate(string strKey, JSONNode nodeData)
	{
		StrKey = strKey;
		Name = nodeData["NAME"];
		Image = nodeData["IMAGE"];
		Category = nodeData["CATEGORY"];

		for (int i = 0; i < (int)eStatusData.MAX; i++)
		{
			eStatusData eStatus = (eStatusData)i;
			double valueData =
				nodeData[eStatus.ToString()].AsDouble;
			StatusData.IncreaseData(eStatus, valueData);
		}
	}


}
