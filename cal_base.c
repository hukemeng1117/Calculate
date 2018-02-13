#include "cal_base.h"

bool cal_compare(const calNode* node1,const calNode* node2) {
	if(node1->calType != node1->calType) {
		return false;
	}
	if(node1->calType == CAL_NUMBER && node1->value == node2->value) {
		return true;
	}
	else if(node1->calType == CAL_OPERATE && node1->operater == node2->operater) {
		return true;
	}
	else if(node1->calType == CAL_BRACKET && node1->bracket == node2->bracket) {
		return true;
	}
	else if(node1->calType == CAL_PUNCK && node1->punck == node2->punck) {
		return true;
	}
	return false;
}