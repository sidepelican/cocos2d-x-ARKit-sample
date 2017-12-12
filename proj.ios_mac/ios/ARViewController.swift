import UIKit
import SceneKit
import ARKit

@available(iOS 11.0, *)
class ARViewController: UIViewController {

    var arView: ARSCNView!
    var tapAnchor: ARAnchor?
    
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
}

// MARK:- ARSCNViewDelegate

@available(iOS 11.0, *)
extension ARViewController: ARSCNViewDelegate {
    
    func renderer(_ renderer: SCNSceneRenderer, willRenderScene scene: SCNScene, atTime time: TimeInterval) {
        
        
    }
}
