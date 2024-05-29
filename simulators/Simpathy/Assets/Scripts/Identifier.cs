using System.Collections;
using System;
using System.Collections.Generic;
using UnityEngine;

public class Identifier : MonoBehaviour
{
    private static int nextId = 0;

    private int id;
    public int Id { get { return id; } }

    private void Awake()
    {
        id = nextId++;
    }
}
