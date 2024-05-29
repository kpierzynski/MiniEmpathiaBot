using System.Collections;
using System;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;
using TMPro;
using System.Linq;

public class Vision : MonoBehaviour
{
    public List<DetectedRobot> robotsInSight = new List<DetectedRobot>();
    public List<DetectedTarget> targetsInSight = new List<DetectedTarget>();

    public float fieldOfViewAngle = 76.0f;
    public float detectionRadius = 7.5f;
    public float targetDetectionRadius = 7.5f;

    void FixedUpdate()
    {
        CheckRobotsNearby();
        CheckTargetsNearby();
        UpdateText();
    }

    private void UpdateText()
    {
        String text = "Found:\n";

        foreach (DetectedRobot robot in robotsInSight)
        {
            text += robot.ToString() + '\n';
        }

        transform.GetChild(0).GetComponent<TextMeshPro>().text = text;
    }

    bool CheckValidHit(Vector3 direction, float radius, string tag, out RaycastHit hit)
    {
        float angle = Vector3.Angle(direction, transform.forward);

        if (angle > fieldOfViewAngle * 0.5f)
        {
            hit = default;
            return false;
        }

        if (!Physics.Raycast(transform.position, direction, out hit)) return false;
        if (Vector3.Distance(transform.position, hit.point) > radius) return false;
        if (!hit.collider.CompareTag(tag)) return false;

        Debug.DrawLine(transform.position, hit.point, Color.blue);

        return true;
    }

    void CheckTargetsNearby()
    {
        targetsInSight.Clear();
        List<GameObject> targets = GameObject.FindGameObjectsWithTag("Target").ToList();
        if (targets.Count == 0) return;

        foreach (GameObject target in targets)
        {
            Vector3 direction = target.transform.position - transform.position;

            RaycastHit hit;
            bool success = CheckValidHit(direction, targetDetectionRadius, "Target", out hit);
            if(!success) return;

            float distance = Vector3.Distance(transform.position, hit.point);
            targetsInSight.Add(new DetectedTarget(distance, direction));
        }
    }

    void CheckRobotsNearby()
    {
        robotsInSight.Clear();
        List<GameObject> robots = GameObject.FindGameObjectsWithTag("Robot").Where(r => r != gameObject.transform.parent.gameObject).ToList();
        if (robots.Count == 0) return;

        foreach (GameObject robot in robots)
        {
            Transform tower = robot.transform.Find("Tower");
            Bounds robotTowerBounds = tower.GetComponent<Collider>().bounds;
            Vector3 towerBottom = new Vector3(robotTowerBounds.center.x, robotTowerBounds.center.y - robotTowerBounds.size.y / 2, robotTowerBounds.center.z);

            Vector3 direction = towerBottom - transform.position;

            RaycastHit hit;
            bool success = CheckValidHit(direction, detectionRadius, "Tower", out hit);
            if (!success) continue;

            Status status = tower.GetComponent<Tower>().Status;
            int id = robot.GetComponent<Identifier>().Id;
            float distance = Vector3.Distance(transform.position, hit.point);

            robotsInSight.Add(new DetectedRobot(id, status, distance, direction));
        }
    }
}
