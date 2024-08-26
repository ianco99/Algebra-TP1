using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class CollisionChecker : MonoBehaviour
{
    [SerializeField] private Transform line1;
    [SerializeField] private Transform line2;

    ////https://www.jeffreythompson.org/collision-detection/line-line.php
    //private bool LineLineCollision(Transform segmentA, Transform segmentB)
    //{
    //    float distancePointOne = ((segmentB.p2.x - segmentB.p1.x) * (segmentA.p1.y - segmentB.p1.y) - ((segmentB.p2.y - segmentB.p1.y) * (segmentA.p1.x - segmentB.p1.x)
    //        / ((segmentB.p2.y - segmentB.p1.y) * (segmentA.p2.x - segmentA.p1.x) - (segmentB.p2.x - segmentB.p1.x) * (segmentA.p2.y - segmentA.p1.y))));
    //
    //    float distancePointTwo = ((segmentA.p2.x - segmentA.p1.x) * (segmentA.p1.y - segmentB.p1.y) - ((segmentA.p2.y - segmentA.p1.y) * (segmentA.p1.x - segmentB.p1.x)
    //        / ((segmentB.p2.y - segmentB.p1.y) * (segmentA.p2.x - segmentA.p1.x) - (segmentB.p2.x - segmentB.p1.x) * (segmentA.p2.y - segmentA.p1.y))));
    //
    //    return distancePointOne >= 0 && distancePointOne <= 1 && distancePointTwo >= 0 && distancePointTwo <= 1;
    //}
    //
    //private Vector2 GetCollisionPoints(Transform segmentA, Transform segmentB)
    //{
    //    float distancePointOne = ((segmentB.p2.x - segmentB.p1.x) * (segmentA.p1.y - segmentB.p1.y) - ((segmentB.p2.y - segmentB.p1.y) * (segmentA.p1.x - segmentB.p1.x)
    //        / ((segmentB.p2.y - segmentB.p1.y) * (segmentA.p2.x - segmentA.p1.x) - (segmentB.p2.x - segmentB.p1.x) * (segmentA.p2.y - segmentA.p1.y))));
    //
    //    float distancePointTwo = ((segmentA.p2.x - segmentA.p1.x) * (segmentA.p1.y - segmentB.p1.y) - ((segmentA.p2.y - segmentA.p1.y) * (segmentA.p1.x - segmentB.p1.x)
    //        / ((segmentB.p2.y - segmentB.p1.y) * (segmentA.p2.x - segmentA.p1.x) - (segmentB.p2.x - segmentB.p1.x) * (segmentA.p2.y - segmentA.p1.y))));
    //
    //    if (distancePointOne >= 0 && distancePointOne <= 1 && distancePointTwo >= 0 && distancePointTwo <= 1)
    //    {
    //        float intersectionX = segmentA.p1.x + (distancePointOne * (segmentA.p2.x - segmentA.p1.x));
    //        float intersectionY = segmentA.p1.y + (distancePointOne * (segmentA.p2.y - segmentA.p1.y));
    //
    //        return Vector2{ intersectionX, intersectionY };
    //    }
    //
    //    return { 0,0 };
    //}
}
