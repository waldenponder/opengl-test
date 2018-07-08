#include "osgViewer/ViewerEventHandlers"

class ChangeWindow : public osgGA::GUIEventHandler
{
public:
	ChangeWindow() { first = false; }
	bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
	{
		if (!first)
		{
			osgViewer::Viewer * viewer = dynamic_cast<osgViewer::Viewer*>(&aa);
			osgViewer::Viewer::Windows ws;
			first = true;
			viewer->getWindows(ws);
			if (!ws.empty())
			{
				osgViewer::Viewer::Windows::iterator iter = ws.begin();
				for (; iter != ws.end(); iter++)
				{
					(*iter)->setWindowRectangle(400, 10, 1000, 1000);
					(*iter)->setWindowDecoration(false);
				}
			}

		}
		return false;
	}
private:
	bool first;
};