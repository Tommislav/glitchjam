#ifndef SOUND_SYSTEM_H
#define SOUND_SYSTEM_H

#include <unordered_map>
#include <string>
#include "Settings.h"
#include "FireBulletComponent.h"
#include "BulletComponent.h"

#include <time.h> // clock_t, clock() and CLOCKS_PER_SEC (milliseconds on windows)

using std::string;


class SoundSystem : public artemis::EntityProcessingSystem
{
	private:

		struct SoundData {
			ofSoundPlayer soundPlayer;
			bool isLoaded;
			int lastPlayed;
			SoundData();
		};

		//artemis::ComponentMapper<PositionComponent> posMapper;
		
		unordered_map<string, SoundData*> soundMap;
		
		
		void createSound(string name, int minPlayTime = 1, bool loop = false) {
			SoundData sd = SoundData();
			soundMap.insert(std::make_pair<string, SoundData*>(name, &sd));
		}

		
		
		void setupSounds() {
			createSound("Laser.wav", 100);
			createSound("Explosion1.wav");


		}
		



		void playSound(string id) {
			SoundData* snd = soundMap[id];
			if (snd != NULL) {
				
				if (!snd->isLoaded) {
					snd->soundPlayer.loadSound(id);
					snd->isLoaded = true;
				}

				// if enough time has passed since last time....

				snd->soundPlayer.play();
			}
		}


	protected:
		virtual bool checkProcessing() {
			return true;
		};

		virtual void begin() {
			// Process all sounds in queue
			std::cout << "PLAY A SOUND!!!" << std::endl;
		};


	public:
		SoundSystem() {
			
		}

		virtual ~SoundSystem() {
			// Destroy all processed sounds!!
		}


		







		virtual void initialize() {
			//posMapper.init(*world);
		}

		virtual void processEntity(artemis::Entity &e) {

			//FireBulletComponent *b = bulMapper.get(e);
			/*
			if (shotFired) {
				if (USE_SOUNDS) {
					if (!soundLoaded) {
						soundLoaded = true;
						pew.loadSound("Laser.wav");
						pew.setVolume(0.1f);
					}

					pew.play();
				}
			}
			*/

		}
};


#endif // SOUND_SYSTEM_H