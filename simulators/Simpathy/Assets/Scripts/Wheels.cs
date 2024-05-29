using System.Collections;
using System.Collections.Generic;
using UnityEngine;


public class WheelsController
{
    const float ROT_SPEED = 360.0f;

    public WheelCollider wheelLeft;
    public WheelCollider wheelRight;

    public WheelsController(WheelCollider left, WheelCollider right)
    {
        wheelLeft = left;
        wheelRight = right;

        wheelLeft.rotationSpeed = ROT_SPEED;
    }

    public void stop()
    {
        wheelLeft.rotationSpeed = 0.0f;
        wheelRight.rotationSpeed = 0.0f;
    }

    public void right()
    {
        wheelLeft.rotationSpeed = ROT_SPEED;
        wheelRight.rotationSpeed = 0.0f;
    }

    public void left()
    {
        wheelRight.rotationSpeed = ROT_SPEED;
        wheelLeft.rotationSpeed = 0.0f;
    }

    public void forward()
    {
        wheelRight.rotationSpeed = ROT_SPEED;
        wheelLeft.rotationSpeed = ROT_SPEED;
    }

    public void backward()
    {
        wheelLeft.rotationSpeed = -ROT_SPEED;
        wheelRight.rotationSpeed = -ROT_SPEED;
    }
}

public class Wheels : MonoBehaviour
{

    public WheelCollider wheelLeft;
    public WheelCollider wheelRight;

    public WheelsController wheels;

    // Start is called before the first frame update
    void Start()
    {
        wheels = new WheelsController(wheelLeft, wheelRight);
    }

    private void Update()
    {
        if (Input.GetKey(KeyCode.W)) wheels.forward();
        else if (Input.GetKey(KeyCode.S)) wheels.backward();
        else if (Input.GetKey(KeyCode.D)) wheels.right();
        else if (Input.GetKey(KeyCode.A)) wheels.left();
        else wheels.stop();
    }

}
