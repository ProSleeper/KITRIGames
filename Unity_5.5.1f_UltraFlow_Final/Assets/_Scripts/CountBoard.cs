using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CountBoard : MonoBehaviour
{
    Camera UiCamera = null;
    Camera WorldCamera = null;

    [SerializeField]
    Transform Target = null;
    Vector3 MovePosition = Vector3.zero;

	UILabel CountLabel = null;

    public Transform TargetTrans
    {
        set
        {
            Target = value;

            if(Target == null)
            {
                Debug.Log("Target is NULL");
            }
        }
    }

    public Camera UI_CAMERA
    {
        get
        {
            if(UiCamera == null)
            {
                UiCamera =
                    NGUITools.FindCameraForLayer(
                        LayerMask.NameToLayer("UI"));
            }

            return UiCamera;
        }
    }

    public Camera WORLD_CAMERA
    {
        get
        {
            if(WorldCamera == null)
            {
                WorldCamera = Camera.main;
            }

            return WorldCamera;
        }
    }

	private void Awake()
	{
		CountLabel =
			gameObject.GetComponentInChildren<UILabel>();

		if (CountLabel == null)
		{
			Debug.Log("Count Label is null");
			return;
		}
	}

	private void Update()
    {
        if (UI_CAMERA == null || WORLD_CAMERA == null)
            return;

        if (Target == null)
            return;

        MovePosition = Target.transform.position;

		Vector3 viewPort =
			WORLD_CAMERA.WorldToViewportPoint(MovePosition);
		Vector3 boardPosition =
			UI_CAMERA.ViewportToWorldPoint(viewPort);

		boardPosition.z = 0f;
		transform.position = boardPosition;
    }
    
	public void SetText(int count)
	{
		CountLabel.text = count.ToString();
		Debug.Log(count);
	}

	public void SelfRemove()
	{
		Destroy(this.gameObject);
	}

}
