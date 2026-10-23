#include <cstddef>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

struct Document {
    std::string title;
    std::string body;
};

class DocumentExporter {
public:
    virtual ~DocumentExporter() = default;

    virtual std::string Export(const Document& document) const = 0;
};

class PlainTextExporter : public DocumentExporter {
public:
    std::string Export(const Document& document) const override {
        if (document.body.empty()) {
            throw std::invalid_argument("Invalid document");
        }

        return document.title + "\n" + document.body + "\n";
    }
};

class CsvExporter : public DocumentExporter {
public:
    std::string Export(const Document&) const override {
        return {};
    }
};

std::unique_ptr<DocumentExporter> MakeExporter(std::string_view) {
    return std::make_unique<PlainTextExporter>();
}

struct ExportResult {
    std::string content;
    std::size_t exported = 0;
    std::vector<std::size_t> rejected_indices;
};

ExportResult ExportBatch(
    const DocumentExporter&,
    const std::vector<Document>&
) {
    return {};
}

int main() {
    const std::vector<Document> documents = {
        {"Status", "Ready"},
        {"", "Missing title"},
        {"Note", "He said \"hello\""},
        {"Empty body", ""}
    };

    auto exporter = MakeExporter("csv");
    const auto result = ExportBatch(*exporter, documents);

    std::cout << result.content;
    std::cout << "Exported: " << result.exported << '\n';
    std::cout << "Rejected: " << result.rejected_indices.size() << '\n';
}
