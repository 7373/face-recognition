#include "AivisionFromChai/Aivision/Seetaface/include/seetaface.h"

float FaceRecognizer::similarity(Seetaface& s, Feature& fa, Feature& fb)
{
	return s.similarity(fa, fb);
}
