

#import "RENode.h"

@class REGLView;

typedef enum {
    kRECameraProjectionOrthographic,
    kRECameraProjectionPerspective,
} kRECameraProjection;

/* RECamera
 *
 * Question: Should camera be a node? The camera itself doesn't need to have a camera, contentSize, z-value, etc...
 */

@interface RECamera : RENode {
    kRECameraProjection projection;    
    
    float frustumLeft, frustumRight;
    float frustumBottom, frustumTop;
    float frustumNear, frustumFar;
    CC3Vector upDirection;
    CC3Vector lookDirection_;
    
    CC3GLMatrix *viewMatrix;
    CC3GLMatrix *projectionMatrix;

    
    BOOL isViewMatrixDirty;
    BOOL isProjectionMatrixDirty;
    
    BOOL areFrustumPlanesDirty_;
    CC3Plane frustumNearPlane_;
    CC3Plane frustumFarPlane_;
    CC3Plane frustumTopPlane_;
    CC3Plane frustumBottomPlane_;
    CC3Plane frustumLeftPlane_;
    CC3Plane frustumRightPlane_;
}

@property (nonatomic, assign) CC3Vector lookDirection;
@property (nonatomic, assign) CC3Vector upDirection;
@property (nonatomic, assign) float frustumLeft, frustumRight, frustumBottom, frustumTop, frustumNear, frustumFar;

@property (nonatomic, readonly) CC3GLMatrix *viewMatrix;
@property (nonatomic, retain) CC3GLMatrix *projectionMatrix; // Can be set from outside. Changing the frustum matrix after this is undefined behavior

- (id)initWithProjection:(kRECameraProjection)p;
- (void)setOrientationWithHorizontalAngle:(float)horizontalAngle verticalAngle:(float)verticalAngle sideTiltAngle:(float)sideTiltAngle;

// Returns the near field point
//- (CC3Vector)convert:(CGPoint)point fromView:(REGLView*)view;

//-(CC3Ray)tmp_unprojectPoint:(CGPoint)cc2Point size:(CGSize)size;
-(CC3Ray)unprojectPoint:(CGPoint)cc2Point inView:(REGLView*)view;

// If it's inside or intersects
- (BOOL)boundingBoxIntersectsFrustum:(CC3BoundingBox)boundingBox; // Only reliable for orthographic projections for now

// Cull test
- (BOOL)globalBoundingBoxCanBeCulled:(CC3BoundingBox)globalBoundingBox;

@end


/*
-(void) populateToLookAt: (CC3Vector) targetLocation
withEyeAt: (CC3Vector) eyeLocation
withUp: (CC3Vector) upDirection;

-(void) populateFromFrustumLeft: (GLfloat) left
andRight: (GLfloat) right
andBottom: (GLfloat) bottom
andTop: (GLfloat) top  
andNear: (GLfloat) near
andFar: (GLfloat) far;

*/