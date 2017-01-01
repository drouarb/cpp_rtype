//
// Created by jonas_e on 1/1/17.
//

#include <UI/CreditLayer.hh>
#include <UI/Window.hh>

std::vector<int> creditTimeline {
        0,
        12,
        17,
        23,
        28,
        33,
        39,
        43,
        48,
        51,
        56, //part 1
        61,
        63,
        67,
        60 + 10,
        60 + 13,
        60 + 18, // part2 OK
        60 + 24,
        60 + 30,
        60 + 35,
        60 + 40,
        60 + 47,
        60 + 52,
        60 + 55,
        60 + 58,
        120 + 3, // part 3
        120 + 5,
        120 + 8,
        120 + 11,
        120 + 15,
        120 + 17,
        120 + 20,
        120 + 25, // charge
        120 + 27,
        120 + 31,
        120 + 33,
        120 + 34,
        120 + 37, // ending
        120 + 39,
        120 + 42,
        120 + 51, //true end
        120 + 57,
        180 + 3,
        180 + 8,
        180 + 14,
        180 + 25,
        180 + 27
};

std::vector<std::string> creditPicturePath {
       "media/credit/p0-0.jpg",
       "media/credit/0alexis.png",
       "media/credit/p0-1.jpg",
       "media/credit/p0-2.jpg",
       "media/credit/p0-3.jpg",
       "media/credit/p0-4.jpg",
       "media/credit/p0-6.jpg",
       "media/credit/0alexis.png",
       "media/credit/p0-41.jpg",
       "media/credit/p0-55.jpg",
       "media/credit/p1-0.jpg",
       "media/credit/p1-1.jpg",
       "media/credit/p1-2.jpg",
       "media/credit/p1-3.jpg",
       "media/credit/p1-4.jpg",
       "media/credit/p1-6.jpg",
       "media/credit/p2-0.jpg",
       "media/credit/0alexis.png",
       "media/credit/p2-1.jpg",
       "media/credit/p2-3.jpg",
       "media/credit/p2-4.jpg",
       "media/credit/0alexis.png",
       "media/credit/p2-5.jpg",
       "media/credit/p2-6.jpg",
       "media/credit/p2-7.jpg",
       "media/credit/p3-0.jpg",
       "media/credit/p3-1.jpg",
       "media/credit/p3-2.jpg",
       "media/credit/p3-004.jpg",
       "media/credit/p3-04.jpg",
       "media/credit/p3-7.jpg",
       "media/credit/0alexis.png",
       "media/credit/pcharge0.jpg",
       "media/credit/pcharge1.jpg",
       "media/credit/pcharge2.jpeg",
       "media/credit/pcharge4.jpg",
       "media/credit/pcharge04.jpg",
       "media/credit/pcharge5.jpg",
       "media/credit/pcharge6.jpg",
       "media/credit/pcharge07.jpg",
       "media/credit/0alexis.png",
       "media/credit/pcharge007.jpg",
       "media/credit/pending0.jpg",
       "media/credit/pending4.jpg",
       "media/credit/pending6.jpg",
       "media/credit/0alexis.png",
};

UI::Credit::Credit() {

}

UI::Credit::~Credit() {

}

void UI::Credit::HereWeGo(UI::UIManager *ui) {
    unsigned long layer = ui->addLayer(UI::GAME, UI::MAIN_WINDOW);
    sf::Clock clock;
    ui->getAudioManager()->playMusic("media/musics/wind.ogg");
    clock.restart();
    ILayer *iLayer = ui->getWindow(MAIN_WINDOW)->getLayer(layer);
    done = true;
    bool flag = true;
    Item *item;
    for (int i = 0; i <= creditPicturePath.size(); i) {
        if (done) {
            item = static_cast<Item*>(iLayer->addItem(UI::ITEM, creditPicturePath[i], 0, 0));
            item->setRatio(LENGTH, WIDTH);
            item->setPosition((LENGTH / 2) - (item->getSprite().getGlobalBounds().width / 2), (WIDTH / 2) - item->getSprite().getGlobalBounds().height / 2);
            i++;
            done = false;
        }
        if (clock.getElapsedTime().asSeconds() > creditTimeline[i]) {
            ui->getWindow(UI::MAIN_WINDOW)->deleteItem(item);
            done = true;
            flag = false;
            if (i == creditPicturePath.size())
                break;
        }
        if (flag) {
            item->setTransparency((int)(clock.getElapsedTime().asSeconds() * 25));
            if (clock.getElapsedTime().asSeconds() * 25 > 255) {
                item->setTransparency(255);
                flag = false;
            }
        }
        //ui->display();
        if (ui->getEventObserver()->received())
            break;
    }
    iLayer->close();
}