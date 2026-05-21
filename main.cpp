#include <iostream>
#include <string>
#include <vector>
#include <memory>

class Alat {
public:
    virtual ~Alat() = default;
    virtual std::string hang() const = 0;
    virtual void info() const;
};

void Alat::info() const {
    std::cout << "[Alat] hang=" << hang() << '\n';
}

class Kutya : public Alat {
public:
    explicit Kutya(std::string nev) : nev_(std::move(nev)) {}
    ~Kutya() override { std::cout << "[Destruktor] " << nev_ << " torolve\n"; }
    std::string hang() const override { return "Vau"; }
    const std::string& nev() const { return nev_; }
private:
    std::string nev_;
};

class Macska : public Alat {
public:
    explicit Macska(std::string nev) : nev_(std::move(nev)) {}
    ~Macska() override { std::cout << "[Destruktor] " << nev_ << " torolve\n"; }
    std::string hang() const override { return "Miau"; }
private:
    std::string nev_;
};

static void keszit_hangot(const Alat& a) {
    a.info();
}

static void statikus_udvozles(const Kutya& k) {
    std::cout << "[EarlyBind] Szia, " << k.nev() << "!\n";
}

int main() {
    std::vector<std::unique_ptr<Alat>> allatok;
    allatok.push_back(std::make_unique<Kutya>("Rex"));
    allatok.push_back(std::make_unique<Macska>("Cica"));
    allatok.push_back(std::make_unique<Kutya>("Buksi"));

    for (const auto& a : allatok)
        keszit_hangot(*a);

    statikus_udvozles(static_cast<const Kutya&>(*allatok[0]));

    std::cout << "[Scope vege] destruktorok koveznek:\n";
}
