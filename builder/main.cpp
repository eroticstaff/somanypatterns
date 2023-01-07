/* Паттерн Builder (Строитель)
 * Классификация: порождающий паттерн
 * Назначение:  позволяет создавать сложные объекты пошагово. Строитель даёт возможность использовать один и тот же код
 *              строительства для получения разных представлений объектов.
 * Применимость:
 *  - Когда вы хотите избавиться от «огромного конструктора».
 *  - Когда ваш код должен создавать разные представления какого-то объекта. Например, деревянные и железобетонные дома
 *  - Когда вам нужно собирать сложные составные объекты.
 *  - Из GoF:
 *     ❑ алгоритм создания сложного объекта не должен зависеть от того, из каких частей состоит объект и как они
 *       стыкуются между собой;
 *     ❑ процесс конструирования должен обеспечивать различные представления конструируемого объекта.
 * Результаты:
 *  ❑ позволяет изменять внутреннее представление продукта. Объект Builder предоставляет распорядителю абстрактный
 *    интерфейс для конструирования продукта, за которым он может скрыть представление и внутреннюю структуру продукта,
 *    а также процесс его сборки. Поскольку продукт конструируется через абстрактный интерфейс, то для изменения
 *    внутреннего представления достаточно всего лишь определить новый вид строителя;
 *  ❑ изолирует код, реализующий конструирование и представление. Паттерн строитель улучшает модульность, инкапсулируя
 *    способ конструирования и представления сложного объекта. Клиентам ничего не надо знать о классах, определяющих
 *    внутреннюю структуру продукта, они отсутствуют в интерфейсе строителя.
 */


#include <iostream>

class MacOSWindow {
public:
    std::string structure;

    void printStructure() {
        std::cout << structure << std::endl;
    }
};

class WindowsWindow {
public:
    std::string structure;

    void printStructure() {
        std::cout << structure << std::endl;
    }
};

class WindowBuilder {
public:
    virtual void createNativeWindow() = 0;

    virtual void addMenubar() = 0;

    virtual void setTitle(std::string title) = 0;

    virtual void setDefaultBackgroundColor() = 0;
};

class MacOSWindowBuilder : public WindowBuilder {
    MacOSWindow *window;

public:
    MacOSWindowBuilder() {
        reset();
    }

    void reset() {
        window = new MacOSWindow;

    }

    ~MacOSWindowBuilder() {
        delete window;
    }

    void createNativeWindow() override {
        window->structure += "Window: Standard MacOS; ";
    }

    void addMenubar() override {
        window->structure += "Menubar: MacOS default; ";
    }

    void setTitle(std::string title) override {
        window->structure += "Window title: " + title + ";";
    }

    void setDefaultBackgroundColor() override {
        window->structure += "Background color: MacOS default; ";
    }

    MacOSWindow *getWindow() {
        return window;
    }
};

class WindowsWindowBuilder : public WindowBuilder {
    WindowsWindow *window;
public:
    WindowsWindowBuilder() {
        reset();
    }

    void reset() {
        window = new WindowsWindow;
    }

    ~WindowsWindowBuilder() {
        delete window;
    }

    void createNativeWindow() override {
        window->structure += "Window: Standard Windows; ";
    }

    void addMenubar() override {
        window->structure += "Menubar: Windows default; ";
    }

    void setTitle(std::string title) override {
        window->structure += "Window title: " + title + ";";
    }

    void setDefaultBackgroundColor() override {
        window->structure += "Background color: Windows default; ";
    }

    WindowsWindow *getWindow() {
        return window;
    }
};

class WindowCreationManager {
    WindowBuilder *m_builder;

public:
    void setBuilder(WindowBuilder *builder) {
        m_builder = builder;
    }

    void createDefaultWindow() {
        m_builder->createNativeWindow();
        m_builder->addMenubar();
        m_builder->setTitle("New Window");
        m_builder->setDefaultBackgroundColor();
    }

    void createWindowWithTitle(std::string title) {
        m_builder->createNativeWindow();
        m_builder->addMenubar();
        m_builder->setTitle(title);
        m_builder->setDefaultBackgroundColor();
    }
};

void client_code(WindowCreationManager *manager) {
    {
        WindowsWindowBuilder *builder = new WindowsWindowBuilder;
        manager->setBuilder(builder);
        manager->createDefaultWindow();
        WindowsWindow *window = builder->getWindow();
        window->printStructure();
        delete window;
        builder->reset();
        manager->createWindowWithTitle("New title");
        window = builder->getWindow();
        window->printStructure();
        delete builder;
    }

    {
        MacOSWindowBuilder *builder = new MacOSWindowBuilder;
        manager->setBuilder(builder);
        manager->createDefaultWindow();
        MacOSWindow *window = builder->getWindow();
        window->printStructure();
        delete window;
        builder->reset();
        manager->createWindowWithTitle("New title");
        window = builder->getWindow();
        window->printStructure();
        delete builder;
    }
}

int main() {
    WindowCreationManager *manager = new WindowCreationManager;
    client_code(manager);
    delete manager;
    return 0;
}
