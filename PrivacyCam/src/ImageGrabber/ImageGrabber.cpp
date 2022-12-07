#include "ImageGrabber.h"

using namespace pricam;

ImageGrabber::ImageGrabber() :
	m_grabState(GrabState::NOT_STARTED)
{
}

ImageGrabber::~ImageGrabber() = default;

GrabState ImageGrabber::GetGrabState() const
{
	return m_grabState;
}

void ImageGrabber::SetGrabState(const GrabState _grabState)
{
	m_grabState = _grabState;
}
