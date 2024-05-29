using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Manager : MonoBehaviour
{
    public float speed = 7.0f;

    void Update()
    {
        Time.timeScale = speed;
    }
}
