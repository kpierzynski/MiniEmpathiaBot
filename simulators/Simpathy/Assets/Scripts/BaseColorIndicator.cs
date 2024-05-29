using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public enum States {
    LookingRandomly, FollowingTarget, FollowingRobot, AtTarget
}

public class BaseColorIndicator : MonoBehaviour
{
    Renderer _renderer;

    Dictionary<States, Color> colors = new Dictionary<States, Color>()
    {
        {States.LookingRandomly, Color.red},
        {States.FollowingRobot, new Color(0.0f, 0.75f, 1.0f) },
        {States.FollowingTarget, new Color(1.0f, 0.75f, 0.0f) },
        {States.AtTarget, Color.green},

    };

    void Start()
    {
        _renderer = this.GetComponent<Renderer>();
    }

    public void SetColorByState(States state)
    {
        _renderer.material.color = colors[state];
    }
}
