using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using SimpleJSON;

// sealed class
// 다른 클래스에서 상속이 불가능
// sealed method -> override x

public sealed class StatusData
 {
	Dictionary<eStatusData, double> DicData = 
		new Dictionary<eStatusData,double>();

	public void InitData()
	{
		DicData.Clear();
	}

	public void Copy(StatusData data)
	{
		foreach(KeyValuePair<eStatusData,double> pair
			in data.DicData)
		{
			IncreaseData(pair.Key, pair.Value);
		}
	}
	
	public void IncreaseData(eStatusData statusData,
		double valueData)
	{
		double preValue = 0.0;
		DicData.TryGetValue(statusData, out preValue);
		DicData[statusData] = preValue + valueData;
	}

	public void DecreaseData(eStatusData statusData,
		double valueData)
	{
		double preValue = 0.0;
		DicData.TryGetValue(statusData, out preValue);
		DicData[statusData] = preValue - valueData;
	}

	public void SetData(eStatusData statusData,
		double valueData)
	{
		DicData[statusData] = valueData;
	}

	public void RemoveData(eStatusData statusData)
	{
		DicData.Remove(statusData);
	}

	public double GetStatusData(eStatusData statusData)
	{
		double preValue = 0.0;
		DicData.TryGetValue(statusData, out preValue);
		return preValue;
	}





	// Simple Type
	//string StrKey = string.Empty;

	//int iAttack = 0;
	//int iDefence = 0;
	//float fCriticalPercent = 0.0f;
	//float fCriticalDamage = 0.0f;
	//float fAttackSpeed = 0.0f;

	//public int Attack
	//{
	//	get	{	return iAttack;	}
	//}
	//public int Defence
	//{
	//	get { return iDefence; }
	//}

	//public float CriticalPercnet
	//{
	//	get
	//	{
	//		return fCriticalPercent;
	//	}
	//}

	//public float CriticalDamage
	//{
	//	get
	//	{
	//		return fCriticalDamage;
	//	}
	//}

	//public float AttackSpeed
	//{
	//	get
	//	{
	//		return fAttackSpeed;
	//	}
	//}

	//public StatusData(string _strKey, JSONNode nodeData)
	//{
	//	StrKey = _strKey;

	//	iAttack = nodeData["Attack"].AsInt;
	//	iDefence = nodeData["Defence"].AsInt;
	//	fCriticalPercent = nodeData["CriticalPercent"].AsFloat;
	//	fCriticalDamage = nodeData["CriticalDamage"].AsFloat;
	//	fAttackSpeed = nodeData["AttackSpeed"].AsFloat;
	//}
}
