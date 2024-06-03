using System.Collections;
using System.Collections.Generic;
using System.Linq;
using UnityEditor;
using UnityEngine;
using UnityEngine.SceneManagement;

public class Goal : MonoBehaviour
{
    private BoxCollider col;
    float startTime;

    void Start()
    {
        this.col = GetComponent<BoxCollider>();
        startTime = Time.time;
    }

    void Update()
    {
        if(AllRobotsInside())
        {
            float time = (Time.time - startTime) / Time.timeScale;

            Debug.Log(time);
            SceneManager.LoadScene(SceneManager.GetActiveScene().name);
        }
    }

    bool AllRobotsInside()
    {
        List<GameObject> robots = GameObject.FindGameObjectsWithTag("Robot").ToList();

        foreach (GameObject robot in robots)
        {
            if (!col.bounds.Contains(robot.transform.position)) return false;
        }

        return true;
    }
}
