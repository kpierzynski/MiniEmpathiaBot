using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RobotSpawner : MonoBehaviour
{
    public GameObject robotPrefab;
    public GameObject plane;

    public int robotCount = 2;

    List<Vector3> usedCoords = new List<Vector3>();

    void Start()
    {
        float robotRadius = 0.85f;
        Bounds planeBounds = plane.GetComponent<Collider>().bounds;

        for (int i = 0; i < robotCount; i++)
        {
            Vector3 point;
            int maxIter = 10;
            do
            {
                point = GetRandomPoint(planeBounds);
            }
            while (!ValidateSpawnPoint(point, usedCoords, robotRadius) && maxIter-- != 0);

            usedCoords.Add(point);
            Instantiate(robotPrefab, point, Quaternion.identity, this.transform);
        }
    }

    private bool ValidateSpawnPoint(Vector3 point, List<Vector3> spawnPoints, float minDistance)
    {
        foreach (Vector3 spawnPoint in spawnPoints)
        {
            if (Vector3.Distance(point, spawnPoint) < minDistance) return false;
        }

        return true;
    }

    private Vector3 GetRandomPoint(Bounds planeBounds)
    {
        float offset = 1.0f;
        float x = Random.Range(-planeBounds.size.x / 2 + offset, planeBounds.size.x / 2 - offset);
        float z = Random.Range(-planeBounds.size.z / 2 + offset, planeBounds.size.z / 2 - offset);

        return new Vector3(x, 0.0f, z);
    }
}
