#pragma once

#include "mayaMVG/maya/context/MVGManipulatorUtil.h"
#include <maya/MPxManipulatorNode.h>

namespace mayaMVG {

class MVGEditCmd;
class MVGContext;

class MVGMoveManipulator: public MPxManipulatorNode
{
	enum EMoveState {
        eMoveNone = 0
        , eMovePoint
        , eMoveEdge
    };
	
	public:
		MVGMoveManipulator();
		virtual ~MVGMoveManipulator();
		
	public:
		static void * creator();
		static MStatus initialize();

	public:
		virtual void postConstructor();
		virtual void draw(M3dView&, const MDagPath&, M3dView::DisplayStyle, M3dView::DisplayStatus);
		virtual MStatus doPress(M3dView &view);
		virtual MStatus doRelease(M3dView &view);
		virtual MStatus doMove(M3dView &view, bool& refresh);
		virtual MStatus doDrag(M3dView& view);
		virtual void preDrawUI(const M3dView&);
		virtual void drawUI(MHWRender::MUIDrawManager&,	const MHWRender::MFrameContext&) const;

	public:
		void setManipUtil(MVGManipulatorUtil* m) { _manipUtil = m; }

	private:
		MPoint updateMouse(M3dView& view, short& mousex, short& mousey);
		// Draw
		void drawCursor(const float mousex, const float mousey);
		void drawIntersections(M3dView& view);
		void drawTriangulation(M3dView& view, MVGManipulatorUtil::DisplayData* data, const float mousex, const float mousey);

		// Compute
		void computeTmpFaceOnMovePoint(M3dView& view, MVGManipulatorUtil::DisplayData* data, const MPoint& mousePoint, bool recompute=false);
		void computeTmpFaceOnMoveEdge(M3dView& view, MVGManipulatorUtil::DisplayData* data, const MPoint& mousePoint, bool recompute=false);
		bool triangulate(M3dView& view, const MVGManipulatorUtil::IntersectionData& intersectionData, const MPoint& mousePointInCameraCoord, MPoint& resultPoint3D);
		bool triangulateEdge(M3dView& view, const MVGManipulatorUtil::IntersectionData& intersectionData, const MPoint& mousePointInCameraCoord, MPointArray& resultPoint3D);

public:
		static MTypeId _id;
		MVGManipulatorUtil* _manipUtil;
		EMoveState _moveState;
        MVector _moveInPlaneColor;
        MVector _moveRecomputeColor;
        MVector _triangulateColor;
        MVector _faceColor;
        MVector _noMoveColor;
        MVector _cursorColor;
};

} // namespace