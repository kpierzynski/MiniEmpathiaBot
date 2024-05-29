using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DetectedRobot
{
    private Vector3 direction;
    private float distance;
    private Status status;
    private int id;

    public Vector3 Direction { get { return direction; } }
    public Status Status { get { return status; } }
    public int Id { get { return id; } }
    public float Distance { get { return distance; } }

    public DetectedRobot(int id, Status status, float distance, Vector3 direction)
    {
        this.id = id;
        this.status = status;
        this.distance = distance;
        this.direction = direction;
    }

    public override string ToString()
    {
        return $"Robot #{id} - {status}.";
    }
}
