import UIKit
import SceneKit
import ARKit

@available(iOS 11.0, *)
class ARViewController: UIViewController {

    private var arView: ARSCNView!
    private var currentAnchor: ARAnchor?
    
    override func viewDidLoad() {
        super.viewDidLoad()
        
        arView = ARSCNView(frame: UIScreen.main.bounds)
        arView.delegate = self
        
        self.view = arView
    }
    
    override func viewWillAppear(_ animated: Bool) {
        super.viewWillAppear(animated)
        
        let config = ARWorldTrackingConfiguration()
        config.planeDetection = .horizontal
        
        // start ARSession
        arView.session.run(config)
    }
    
    override func viewDidDisappear(_ animated: Bool) {
        super.viewDidDisappear(animated)
        
        arView.session.pause()
    }
    
    @objc func hitTest(glNormalizedPoint: CGPoint) {
        guard let currentFrame = arView.session.currentFrame else { return }
        
        // convert GL point to UIKit point.
        let tapPointNormalized = CGPoint(x: glNormalizedPoint.x, y: 1.0 - glNormalizedPoint.y)
        
        // transform point from device orientation.
        let videoSize = view.bounds.size
        let tapPointTransform = currentFrame.displayTransform(for: UIApplication.shared.statusBarOrientation, viewportSize: videoSize)
        let testPoint = tapPointNormalized.applying(tapPointTransform)
        
        // try hitTest
        let results = currentFrame.hitTest(testPoint, types: .existingPlane)
        guard let result = results.first else { return }
        
        // keep result transform
        currentAnchor = ARAnchor(transform: result.worldTransform)
    }
    
    private func anchorToCameraTransform(anchor: ARAnchor) -> SCNMatrix4 {
        guard let originToCameraTransform = arView.pointOfView?.worldTransform else { return SCNMatrix4Identity }
        let originToAnchorTransform = SCNMatrix4(anchor.transform)
        let anchorToCameraTransform = SCNMatrix4Mult(originToCameraTransform, SCNMatrix4Invert(originToAnchorTransform))
        
        return anchorToCameraTransform
    }
}

// MARK:- ARSCNViewDelegate

@available(iOS 11.0, *)
@objc extension ARViewController: ARSCNViewDelegate {
    
    func renderer(_ renderer: SCNSceneRenderer, didAdd node: SCNNode, for anchor: ARAnchor) {
        if currentAnchor == nil {
            currentAnchor = anchor
        }
    }
    
    func renderer(_ renderer: SCNSceneRenderer, willRenderScene scene: SCNScene, atTime time: TimeInterval) {
        guard let anchor = currentAnchor else { return }
        guard let currentFrame = arView.session.currentFrame else { return }
        
        let transform = anchorToCameraTransform(anchor: anchor)
        let projection = SCNMatrix4(currentFrame.camera.projectionMatrix)
        
        ARKitHelper.cameraMatrixUpdated(transform, projection: projection)
    }
}
