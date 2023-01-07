/* Паттерн Abstact Factory (Абстрактная фабрика)
 * Классификация: порождающий паттерн
 * Назначение:  позволяет создавать семейства связанных объектов, не привязываясь к конкретным классам создаваемых
 *              объектов.
 * Применимость:
 *  - Когда бизнес-логика программы должна работать с разными видами связанных друг с другом продуктов, не завися от
 *    конкретных классов продуктов
 *  - Из GoF:
 *      ❑ система не должна зависеть от того, как создаются, компонуются и представляются входящие в нее объекты;
 *      ❑ входящие в семейство взаимосвязанные объекты должны использоваться вместе и вам необходимо обеспечить
 *        выполнение этого ограничения;
 *      ❑ система должна конфигурироваться одним из семейств составляющих ее объектов;
 *      ❑ вы хотите предоставить библиотеку объектов, раскрывая только их интерфейсы, но не реализацию.
 *  Результаты:
 *  ❑ изолирует конкретные классы. Помогает контролировать классы объектов, создаваемых приложением. Поскольку фабрика
 *    инкапсулирует ответственность за создание классов и сам процесс их создания, то она изолирует клиента от деталей
 *    реализации классов. Клиенты манипулируют экземплярами через их абстрактные интерфейсы. Имена изготавливаемых
 *    классов известны только конкретной фабрике, в коде клиента они не упоминаются;
 *  ❑ упрощает замену семейств продуктов. Класс конкретной фабрики появляется в приложении только один раз: при
 *    инстанцировании. Это облегчает замену используемой приложением конкретной фабрики. Приложение может изменить
 *    конфигурацию продуктов, просто подставив новую конкретную фабрику. Поскольку абстрактная фабрика создает все
 *    семейство продуктов, то и заменяется сразу все семейство. В нашем примере пользовательского интерфейса перейти от
 *    виджетов Motif к виджетам Presentation Manager можно, просто переключившись на продукты соответствующей фабрики и
 *    заново создав интерфейс;
 *  ❑ гарантирует сочетаемость продуктов. Если продукты некоторого семейства спроектированы для совместного
 *    использования, то важно, чтобы приложение в каждый момент времени работало только с продуктами единственного
 *    семейства. Класс AbstractFactory позволяет легко соблюсти это ограничение;
 *  ❑ поддержать новый вид продуктов трудно. Расширение абстрактной фабрики для изготовления новых видов
 *    продуктов – непростая задача. Интерфейс AbstractFactory фиксирует набор продуктов, которые можно создать.
 *    Для поддержки новых продуктов необходимо расширить интерфейс фабрики, то есть изменить класс AbstractFactory и
 *    все его подклассы. Решение этой проблемы мы обсудим в разделе «Реализация».
 *
 */

#include <iostream>
#include <string>

class Button {
public:
    virtual void buttonClick() = 0;

    virtual ~Button() = default;

};

class TextEdit {
protected:
    std::string m_text;
public:
    virtual const std::string &getText() = 0;

    virtual void setText(std::string text) = 0;

    virtual ~TextEdit() = default;

};


class WindowsButton : public Button {
public:
    void buttonClick() override {
        //Windows native handling
        std::cout << "Windows button was clicked" << std::endl;
    }
};

class WindowsTextEdit : public TextEdit {
public:
    const std::string &getText() override {

        //Windows native handling
        return m_text;
    }

    void setText(std::string text) override {
        //Windows native handling
        m_text = text;
        std::cout << "Windows TextEdit text set to " << "'" << m_text << "'" << std::endl;
    }
};


class MacOSButton : public Button {
public:
    void buttonClick() override {
        //MacOS native handling
        std::cout << "MacOS button was clicked" << std::endl;
    }
};

class MacOSTextEdit : public TextEdit {
public:
    const std::string &getText() override {
        //MacOS native handling
        return m_text;
    }

    void setText(std::string text) override {
        //MacOS native handling
        m_text = text;
        std::cout << "MacOS TextEdit text set to " << "'" << m_text << "'" << std::endl;
    }
};


class WindowApplication {
public:
    virtual Button *createButton() = 0;

    virtual TextEdit *createTextEdit() = 0;

    virtual ~WindowApplication() = default;
};

class WindowsWindowApplication : public WindowApplication {
public:
    Button *createButton() override {
        return new WindowsButton;
    }

    TextEdit *createTextEdit() override {
        return new WindowsTextEdit;
    }
};

class MacOSWindowApplication : public WindowApplication {
public:
    Button *createButton() override {
        return new MacOSButton;
    }

    TextEdit *createTextEdit() override {
        return new MacOSTextEdit;
    }
};

enum class OS {
    Windows,
    MacOS,
    None
};

#define PLATFORM_WINDOWS 1
#define PLATFORM_MACOS 0


#if PLATFORM_WINDOWS
const OS USED_API = OS::Windows;
#elif PLATFORM_MACOS
const OS USED_API = OS::MacOS;
#else
const OS USED_API = OS::None;
#endif

void client_code(WindowApplication *application) {
    Button *button = application->createButton();
    TextEdit *textEdit = application->createTextEdit();

    button->buttonClick();
    textEdit->setText("Hello OS");
    std::cout << "Text edit have text -> " << textEdit->getText() << std::endl;

    delete button;
    delete textEdit;
}

int main() {
    WindowApplication *app;
    switch (USED_API) {
        case OS::Windows:
            app = new WindowsWindowApplication;
            break;
        case OS::MacOS:
            app = new MacOSWindowApplication;
            break;
        default:
            std::cout << "None of platforms is chosen!";
            return 1;
    }

    client_code(app);

    delete app;
    return 0;
}
