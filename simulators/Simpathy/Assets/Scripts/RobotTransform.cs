/*using System.Collections;
using System.Collections.Generic;
using System.Linq;
using Unity.VisualScripting;
using UnityEngine;

public class RobotTransform : MonoBehaviour
{
    List<GameObject> otherRobots;
    float spentTime = 0.0f;

    Status status { get { return GetComponentInChildren<Tower>().Status; } }

    float detectionRange = 3.0f;
    public int minNeighboursNearby = 3;
    public float minNearbyTimeByAllies = 4.0f;
    public float minNearbyTimeByEnemies = 16.0f;

    void Start()
    {
        otherRobots = GameObject.FindGameObjectsWithTag("Robot").Where(r => r != gameObject).ToList();
    }

    void Update()
    {
        if (status.IsEnemy) EnemyBehaviour();
        else AllyBehaviour();
    }

    void AllyBehaviour()
    {
        int allies = 0;
        int enemies = 0;

        foreach (GameObject neighbour in otherRobots)
        {
            if (Vector3.Distance(transform.position, neighbour.transform.position) > detectionRange) continue;
            Status neighbourStatus = neighbour.GetComponentInChildren<Tower>().Status;

            if (neighbourStatus.IsBeingCaptured == true) continue;

            if (neighbourStatus.IsEnemy) enemies++;
            else allies++;
        }

        if (enemies > allies)
        {
            spentTime += Time.deltaTime;
            status.IsBeingCaptured = true;
        }
        else
        {
            spentTime = 0.0f;
            status.IsBeingCaptured = false;
        }

        if (spentTime > minNearbyTimeByEnemies)
        {
            status.IsEnemy = true;
            status.IsBeingCaptured = false;
            spentTime = 0.0f;
        }
    }

    void EnemyBehaviour()
    {
        int neighbours = 0;
        foreach (GameObject neighbour in otherRobots)
        {
            Status neighbourStatus = neighbour.GetComponentInChildren<Tower>().Status;

            if (neighbourStatus.IsBeingCaptured == true || neighbourStatus.IsEnemy == true) continue;

            if (Vector3.Distance(transform.position, neighbour.transform.position) < detectionRange)
                neighbours++;
        }

        if (neighbours >= minNeighboursNearby)
        {
            spentTime += Time.deltaTime;
            status.IsBeingCaptured = true;
        }
        else
        {
            spentTime = 0.0f;
            status.IsBeingCaptured = false;
        }

        if (spentTime > minNearbyTimeByAllies)
        {
            status.IsAlly = true;
            status.IsBeingCaptured = false;
            spentTime = 0.0f;
        }
    }
}
*/