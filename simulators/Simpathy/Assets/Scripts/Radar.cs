using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Radar : MonoBehaviour
{
    public float maxDistance = 4.0f;

    private float[] distances = new float[3];
    public float[] Distances { get { return distances; } }

    private Color[] rayColors = new Color[3]
    {
        Color.yellow,
        new Color(1, 165/255, 0),
        Color.red
    };

    void Update()
    {
        RaycastHit hit;
        for (int i = -1; i <= 1; i++)
        {
            float angle = 45 * i;

            Vector3 direction = Quaternion.Euler(0, angle, 0) * transform.forward;
            if (Physics.Raycast(transform.position, direction, out hit, maxDistance))
            {
                distances[i + 1] = hit.distance;
                Debug.DrawLine(transform.position, hit.point, rayColors[i + 1]);
            }
            else distances[i + 1] = maxDistance;
        }
    }
}
