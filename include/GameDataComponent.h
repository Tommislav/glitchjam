#ifndef GAMEDATACOMPONENT_H
#define GAMEDATACOMPONENT_H

class GameDataComponent : public artemis::Component {
	public:
		int level;
		int wave;
		int lives;
		int score;

		int swarmsAlive;
		int enemiesAlive;

		int swarmCountdown;

		GameDataComponent(): level(0), wave(0), lives(3), score(0), swarmsAlive(0), enemiesAlive(0), swarmCountdown(300) {}
		~GameDataComponent(){}
};

#endif // GAMEDATACOMPONENT_H
