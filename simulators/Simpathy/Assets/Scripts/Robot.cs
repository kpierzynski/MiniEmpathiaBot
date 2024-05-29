using System.Collections;
using System.Collections.Generic;
using System.Linq;
using Unity.VisualScripting;
using UnityEditor.XR;
using UnityEngine;

enum Direction
{
    Left, Forward, Right, Backward
}

public class Robot : MonoBehaviour
{
    [SerializeField]
    private bool egoistic;
    public bool Egoistic {  get { return egoistic; } }

    private Vision vision;
    private WheelsController wheels;
    private Radar radar;
    private Tower tower;

    private Direction currentDirection;
    private float changeProb = 0.0f;

    void Start()
    {
        vision = this.GetComponentInChildren<Vision>();
        wheels = this.GetComponent<Wheels>().wheels;
        radar = this.GetComponentInChildren<Radar>();
        tower = this.GetComponentInChildren<Tower>();
    }

    void Update()
    {
        List<GameObject> list = GameObject.FindGameObjectsWithTag("Target").ToList();
        foreach (GameObject go in list)
        {
            float distance = Vector3.Distance(transform.position, go.transform.position);
            if (distance < 1.05f)
            {
                wheels.stop();
                return;
            }
            else if (distance < 1.3f)
            {
                tower.Status.IsAtTarget = true;
                return;
            }

            tower.Status.IsAtTarget = false;
        }

        List<DetectedTarget> targets = vision.targetsInSight.OrderBy(r => r.Distance).ToList();
        DetectedTarget target = targets.FirstOrDefault();

        if (target != null)
        {

            float product = Vector3.Cross(target.Direction, this.transform.forward).y;
            Drive(product);
            tower.Status.IsSeeingTarget = true;
            return;
        }

        if (!egoistic) { 
        List<DetectedRobot> robots = vision.robotsInSight.Where(r => r.Status.IsSeeingTarget || r.Status.IsFollowingRobot || r.Status.IsAtTarget).OrderBy(r => r.Distance).ToList();
        DetectedRobot robot = robots.FirstOrDefault();

        if (robot != null)
        {
            float product = Vector3.Cross(robot.Direction, this.transform.forward).y;
            Drive(product);
            tower.Status.IsFollowingRobot = true;
            return;
        }
    }

        tower.Status.IsLookingRandomly = true;
        SearchRandomly();
    }

    void Drive(float direction)
    {
        float epsilon = 0.1f;   // smoothing forward movement

        if (direction > epsilon) wheels.left();
        else if (direction < -epsilon) wheels.right();
        else wheels.forward();
    }

    void ApplyDirection(Direction direction)
    {
        switch (direction)
        {
            case Direction.Left:
                wheels.left();
                break;

            case Direction.Right:
                wheels.right();
                break;

            case Direction.Forward:
                wheels.forward();
                break;

            case Direction.Backward:
                wheels.backward();
                break;
        }
    }

    void SearchRandomly()
    {
        if (Random.value < changeProb)
        {
            changeProb = 0.0f;

            currentDirection = (Direction)Random.Range(0, 4);
        }

        changeProb += 0.01f * Time.deltaTime;
        changeProb = Mathf.Clamp01(changeProb);

        ApplyDirection(currentDirection);
    }

}
