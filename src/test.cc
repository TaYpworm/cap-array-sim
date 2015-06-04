#include <entityx/entityx.h>

namespace ex = entityx;

class Application : public ex::EntityX {
public:
	explicit Application() {
		systems.configure();
	}

	void Update(ex::TimeDelta dt) {

	}
};

int main(){
	ex::EntityX entityx;

	ex::Entity entity = entityx.entities.create();
}