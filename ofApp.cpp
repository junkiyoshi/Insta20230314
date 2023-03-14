#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openFrameworks");

	ofBackground(255);
	//ofEnableBlendMode(ofBlendMode::OF_BLENDMODE_ADD);
}

//--------------------------------------------------------------
void ofApp::update() {

	for (int i = this->location_list.size() - 1; i >= 0; i--) {

		this->size_list[i] += this->speed_list[i];
		this->location_list[i] += this->directon_list[i];

		if (this->size_list[i] > this->max_size_list[i]) {

			this->location_list.erase(this->location_list.begin() + i);
			this->directon_list.erase(this->directon_list.begin() + i);
			this->size_list.erase(this->size_list.begin() + i);
			this->speed_list.erase(this->speed_list.begin() + i);
			this->max_size_list.erase(this->max_size_list.begin() + i);
			this->deg_list.erase(this->deg_list.begin() + i);
			this->color_list.erase(this->color_list.begin() + i);
		}
	}

	ofColor color;
	for (int i = 0; i < 3; i++) {

		auto location = glm::vec2();
		this->location_list.push_back(location);
		auto direction = glm::normalize(glm::vec2(ofRandom(-5, 5), ofRandom(-5, 5))) * ofRandom(3, 10);
		this->directon_list.push_back(direction);
		this->size_list.push_back(1);
		this->speed_list.push_back(ofRandom(1, 2));
		this->max_size_list.push_back(ofRandom(20, 100));
		this->deg_list.push_back(ofRandom(360));
		color.setHsb(ofRandom(255), 255, 255);
		this->color_list.push_back(color);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);
	ofNoFill();

	for (int i = 0; i < this->location_list.size(); i++) {

		ofPushMatrix();
		ofTranslate(this->location_list[i]);
		ofRotate(this->deg_list[i]);

		vector<glm::vec2> vertices;

		for (int deg = 0; deg < 360; deg += 2) {

			vertices.push_back(this->make_point(deg * DEG_TO_RAD) / 30 * this->size_list[i]);
		}

		auto alpha_1 = this->size_list[i] > this->max_size_list[i] * 0.6 ? ofMap(this->size_list[i], this->max_size_list[i] * 0.6, this->max_size_list[i], 255, 0) : 255;
		auto alpha_2 = this->size_list[i] > this->max_size_list[i] * 0.6 ? ofMap(this->size_list[i], this->max_size_list[i] * 0.6, this->max_size_list[i], 255, 32) : 255;

		ofFill();
		ofSetColor(this->color_list[i], alpha_1);

		ofBeginShape();
		ofVertices(vertices);
		ofEndShape(true);

		ofNoFill();
		ofSetColor(this->color_list[i], alpha_2);

		ofBeginShape();
		ofVertices(vertices);
		ofEndShape(true);

		ofPopMatrix();
	}
}

//--------------------------------------------------------------
//Reference by https://twitter.com/shiffman/status/1095764239665512453
glm::vec2 ofApp::make_point(float theta) {

	float x = 16 * (pow(sin(theta), 3));
	float y = 13 * cos(theta) - 5 * cos(2 * theta) - 2 * cos(3 * theta) - cos(4 * theta);
	return glm::vec2(x, -y);
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}