#ifndef DESIGN_PATTERNS_STRUCTURAL_FACADE_H
#define DESIGN_PATTERNS_STRUCTURAL_FACADE_H

#include <iostream>
#include <memory>
#include <string>

namespace DesignPatterns::Facade {

// 子系统组件1：投影仪
class Projector {
    public:
        void on() { std::cout << "投影仪已开启" << std::endl; }
        void off() { std::cout << "投影仪已关闭" << std::endl; }
        void setInput(const std::string& input) { 
            std::cout << "投影仪输入源设置为: " << input << std::endl; 
        }
    };
    
// 子系统组件2：音响系统
class SoundSystem {
public:
    void on() { std::cout << "音响系统已开启" << std::endl; }
    void off() { std::cout << "音响系统已关闭" << std::endl; }
    void setVolume(int level) { 
        std::cout << "音量设置为: " << level << std::endl; 
    }
};

// 子系统组件3：蓝光播放器
class BluRayPlayer {
public:
    void on() { std::cout << "蓝光播放器已开启" << std::endl; }
    void off() { std::cout << "蓝光播放器已关闭" << std::endl; }
    void play(const std::string& movie) { 
        std::cout << "开始播放电影: " << movie << std::endl; 
    }
    void stop() { std::cout << "停止播放" << std::endl; }
};

// 子系统组件4：灯光控制
class Lights {
public:
    void dim(int level) { 
        std::cout << "灯光调暗至: " << level << "%" << std::endl; 
    }
    void on() { std::cout << "灯光全开" << std::endl; }
};

// 外观类：家庭影院外观
class HomeTheaterFacade {
private:
    std::shared_ptr<Projector> projector;
    std::shared_ptr<SoundSystem> soundSystem;
    std::shared_ptr<BluRayPlayer> bluRayPlayer;
    std::shared_ptr<Lights> lights;

public:
    HomeTheaterFacade() {
        projector = std::make_shared<Projector>();
        soundSystem = std::make_shared<SoundSystem>();
        bluRayPlayer = std::make_shared<BluRayPlayer>();
        lights = std::make_shared<Lights>();
    }

    // 简化接口：观看电影
    void watchMovie(const std::string& movie) {
        std::cout << "\n=== 准备观看电影 ===" << std::endl;
        lights->dim(10);
        projector->on();
        projector->setInput("HDMI");
        soundSystem->on();
        soundSystem->setVolume(20);
        bluRayPlayer->on();
        bluRayPlayer->play(movie);
    }

    // 简化接口：结束观看
    void endMovie() {
        std::cout << "\n=== 结束观看 ===" << std::endl;
        bluRayPlayer->stop();
        bluRayPlayer->off();
        soundSystem->off();
        projector->off();
        lights->on();
    }

    // 简化接口：只听音乐
    void listenToMusic() {
        std::cout << "\n=== 只听音乐模式 ===" << std::endl;
        lights->dim(30);
        soundSystem->on();
        soundSystem->setVolume(15);
        std::cout << "音乐播放中..." << std::endl;
    }
};

} // namespace DesignPatterns::Facade


#endif