#include <iostream>
#include <gtkmm.h>
#include <gtkmm/button.h>


class QuizisWindow : public Gtk::Window
{
public:
  QuizisWindow(){
    set_border_width(10);
    set_default_size(200, 200);
    add(hbox);

    Gtk::Button *button = new Gtk::Button("hello");
    Gtk::Button *button2 = new Gtk::Button("world");
    hbox.add(*button);
    hbox.add(*button2);

    hbox.show_all();

  };
  ~QuizisWindow(){};

protected:
  Gtk::VBox hbox;

};




int main(int argc, char *argv[])
{
  auto app = Gtk::Application::create(argc, argv, "org.gtkmm.examples.base");

  QuizisWindow window;


  return app->run(window);

}
