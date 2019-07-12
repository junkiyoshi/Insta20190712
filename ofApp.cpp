#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetColor(39);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	auto radius = 10;
	auto span = 60;
	auto margin = 60;
	for (int x = margin; x <= ofGetWidth() - margin; x += span) {

		for (int y = margin; y <= ofGetHeight() - margin; y += span) {

			auto location = glm::vec2(x, y);
			auto location_noise_value = ofNoise(location.x * 0.005, location.y * 0.005, ofGetFrameNum() * 0.008);
		
			vector<glm::vec2> vertices;
			if (location_noise_value > 0.55) {

				for (int deg = 0; deg < 360; deg++) {

					auto noise_location = location + glm::vec2(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD));
					auto noise_radius = ofMap(ofNoise(noise_location.x * 0.45, noise_location.y * 0.45, ofGetFrameNum() * 0.005), 0, 1, radius, radius * 3);
					auto tmp_radius = radius + noise_radius * ofMap(location_noise_value, 0.55, 1, 0, 1);

					vertices.push_back(glm::vec2(tmp_radius * cos(deg * DEG_TO_RAD), tmp_radius * sin(deg * DEG_TO_RAD)));
				}
			}
			else {

				for (int deg = 0; deg < 360; deg++) {

					vertices.push_back(glm::vec2(radius * cos(deg * DEG_TO_RAD), radius * sin(deg * DEG_TO_RAD)));
				}
			}

			ofPushMatrix();
			ofTranslate(location);

			ofBeginShape();
			ofVertices(vertices);
			ofEndShape();

			ofPopMatrix();
		}
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}