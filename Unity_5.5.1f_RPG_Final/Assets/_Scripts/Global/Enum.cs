
public enum eBaseObjectState
{
	STATE_NORMAL,
	STATE_DIE,
}

public enum eStateType
{
	STATE_NONE = 0,
	STATE_IDLE,
	STATE_ATTACK,
	STATE_WALK,
	STATE_DEAD
}

public enum eStatusData
{
	MAX_HP,
	ATTACK,
	DEFFENCE,
	MAX,
}

public enum eTeamType
{
	TEAM_1,
	TEAM_2,
}


// Monster 관련
public enum eRegeneratorType
{
	NONE,
	REGENTIME_EVENT,
	TRIGGER_EVENT,
}

public enum eMonsterType
{
	A_Monster,
	B_Monster,
	C_Monster,
	MAX,
}

// Skill 관련
public enum eSkillTemplateType
{
	TARGET_ATTACK,
	RANGE_ATTACK,
}

public enum eSkillAttackRangeType
{
	RANGE_BOX,
	RANGE_SPHERE,
}

public enum eSkillModelType
{
	CIRCLE,
	BOX,
	MAX
}

