using System;
using System.Linq;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.Transactions;

[Serializable]
public class Status
{
    private const int DEFAULT_STATUS = 0b00001;
    private const int LOOKING_RANDOMLY_MASK = 1;
    private const int FOLLOWING_ROBOT_MASK = 2;
    private const int SEEING_TARGET_MASK = 3;
    private const int AT_TARGET_MASK = 4;

    public delegate void StatusChange(Status status);
    public event StatusChange OnStatusChange;

    [SerializeField]
    private int _status = DEFAULT_STATUS;      // not being captured, not enemy, 1 (to keep this non zero)
    private int status
    {
        get { return _status; }
        set
        {
            _status = value;
            OnStatusChange?.Invoke(this);
        }
    }

    public bool IsLookingRandomly
    {
        get { return (status & (1 << LOOKING_RANDOMLY_MASK)) > 0; }
        set
        {
            status = 1;
            if (value) status |= (1 << LOOKING_RANDOMLY_MASK);
            else status &= ~(1 << LOOKING_RANDOMLY_MASK);
        }
    }

    public bool IsFollowingRobot
    {
        get { return (status & (1 << FOLLOWING_ROBOT_MASK)) > 0; }
        set
        {
            status = 1;
            if (value) status |= (1 << FOLLOWING_ROBOT_MASK);
            else status &= ~(1 << FOLLOWING_ROBOT_MASK);
        }
    }

    public bool IsSeeingTarget
    {
        get { return (status & (1 << SEEING_TARGET_MASK)) > 0; }
        set
        {
            status = 1;
            if (value) status |= (1 << SEEING_TARGET_MASK);
            else status &= ~(1 << SEEING_TARGET_MASK);
        }
    }


    public bool IsAtTarget
    {
        get { return (status & (1 << AT_TARGET_MASK)) > 0; }
        set
        {
            status = 1;
            if (value) status |= (1 << AT_TARGET_MASK);
            else status &= ~(1 << AT_TARGET_MASK);
        }
    }

    public int Value { get { return status; } set { status = value; } }

    public Status(int value)
    {
        _status = value;
    }

    public Status()
    {
        _status = DEFAULT_STATUS;
    }

}
public class Tower : MonoBehaviour
{
    readonly Color[] colors = new Color[3]
    {
        Color.red, Color.green, Color.blue
    };

    [SerializeField]
    private Status status = new Status();
    public Status Status { get { return status; } }

    BaseColorIndicator indicator;

    public void OnValidate()
    {
        // Trick to reload and recompute tower colors from Unity's editor change of value.
        if (gameObject.activeInHierarchy) status.Value = status.Value;
    }

    void Start()
    {
        SetStatus(status.Value);
        status.OnStatusChange += OnStatusChange;

        indicator = gameObject.transform.parent.GetComponentInChildren<BaseColorIndicator>();
        UpdateColor();
    }

    private void OnStatusChange(Status status)
    {
        SetStatus(status.Value);
        UpdateColor();
    }

    public void UpdateColor()
    {
        if (status.IsLookingRandomly) indicator.SetColorByState(States.LookingRandomly);
        if (status.IsFollowingRobot) indicator.SetColorByState(States.FollowingRobot);
        if (status.IsSeeingTarget) indicator.SetColorByState(States.FollowingTarget);
        if (status.IsAtTarget) indicator.SetColorByState(States.AtTarget);
    }

    public void SetStatus(int status)
    {
        string number = ConvertToBase(status, 3);

        int index = 0;

        foreach (Transform child in this.transform)
        {
            Renderer renderer = child.GetComponent<Renderer>();
            renderer.sharedMaterial.color = Color.white;

            if (index >= number.Length) continue;

            int colorIndex = number[index] - '0';
            renderer.material.color = colors[colorIndex];

            index++;

        }
    }

    private string ConvertToBase(int number, int baseValue)
    {
        if (baseValue < 2 || baseValue > 9)
        {
            throw new ArgumentException("Base must be between 2 and 9");
        }

        if (number == 0) return "0";

        string result = "";
        while (number > 0)
        {
            int remainder = number % baseValue;
            result = remainder.ToString() + result;
            number /= baseValue;
        }

        return result;
    }

}
