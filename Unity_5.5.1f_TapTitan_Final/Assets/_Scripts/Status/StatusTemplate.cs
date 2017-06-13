using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using SimpleJSON;

// Json 로드 형태
public class StatusTemplate
{
	string StrKey = string.Empty;
	StatusData StatusData = new StatusData();

	public string KEY { get { return StrKey; } }
	public StatusData STATUS_DATA { get { return StatusData; } }
	
	public StatusTemplate(string strKey, JSONNode nodeData)
	{
		StrKey = strKey;
		for(int i = 0; i < (int)eStatusData.MAX; i++)
		{
			eStatusData eStatus = (eStatusData)i;
			double valueData = 
				nodeData[eStatus.ToString()].AsDouble;
			StatusData.IncreaseData(eStatus, valueData);
		}
	}
}
