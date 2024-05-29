using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DetectedTarget
{
    private Vector3 direction;
    private float distance;

    public Vector3 Direction { get { return direction; } }
    public float Distance { get { return distance; } }

    public DetectedTarget(float distance, Vector3 direction)
    {
        this.distance = distance;
        this.direction = direction;
    }

    public override string ToString()
    {
        return $"Robot #{direction.ToString()} - {distance.ToString()}.";
    }

}
