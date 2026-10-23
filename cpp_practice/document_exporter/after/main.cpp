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
    std::string Export(const Document& doc) const override {
        if (doc.title.empty()) {
            throw std::invalid_argument("[PlainTextExporter] Invalid document");
        }

        return doc.title + "\n" + doc.body + "\n";
    }
};

class CsvExporter : public DocumentExporter {
private:
    static std::string ParseString(const std::string& s) {
        std::string res;

        for (char ch : s) {
            if (ch == '"') {
                res += "\"\"";
            } else {
                res += ch;
            }
        }

        return res;
    }

public:
    std::string Export(const Document& doc) const override {
        if (doc.title.empty()) {
            throw std::invalid_argument("[CsvExporter] Invalid Document");
        }

        return "\"" + ParseString(doc.title) + "\",\"" + ParseString(doc.body) + "\"" + "\n"; 
    }
};

std::unique_ptr<DocumentExporter> MakeExporter(std::string_view type) {
    if (type == "text") {
        return std::make_unique<PlainTextExporter>();
    } else if (type == "csv") {
        return std::make_unique<CsvExporter>();
    }

    throw std::invalid_argument("There is no exporter for choosen type");
}

struct ExportResult {
    std::string content;
    std::size_t exported = 0;
    std::vector<std::size_t> rejected_indices;
};

ExportResult ExportBatch(const DocumentExporter& exporter, const std::vector<Document>& docs) {
    ExportResult result;

    for (std::size_t i = 0; i < docs.size(); ++i) {
        const Document& doc = docs[i];

        try {
            result.content += exporter.Export(doc);
            ++result.exported;
        } catch (const std::invalid_argument& e) {
            result.rejected_indices.push_back(i);
            std::cerr << e.what() << "\n";
        }
    }

    return result;
}

int main() {
    const std::vector<Document> documents = {
        {"Status", "Ready"},
        {"", "Missing title"},
        {"Note", "He said \"hello\""},
        {"Empty body", ""}
    };

    std::unique_ptr<DocumentExporter> exporter = MakeExporter("csv");
    const ExportResult result = ExportBatch(*exporter, documents);

    std::cout << result.content;
    std::cout << "Exported: " << result.exported << '\n';
    std::cout << "Rejected: " << result.rejected_indices.size() << '\n';

    return 0;
}
