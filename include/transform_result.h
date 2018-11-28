//
// Created by Christian Ledergerber on 15.11.18.
//

#ifndef RAPIDJSON_FAILURE_COLLECTION_H
#define RAPIDJSON_FAILURE_COLLECTION_H

#include <cassert>
#include <optional>
#include <string>
#include <vector>

#include "failure.h"

namespace rapidoson {

    namespace internal {

        class FailureCollection {
        public:
            FailureCollection() {}

            FailureCollection(const Failure & failure) {
                failures_.push_back(failure);
            }

            const std::vector<Failure>& GetFailures() const {
                return failures_;
            }

            void Append(const FailureCollection& other) {
                auto other_vector = other.GetFailures();
                std::copy(other_vector.begin(), other_vector.end(), std::back_inserter(failures_));
            }

            void Append(const Failure& other) {
                failures_.push_back(other);
            }

            void AddPath(const std::string& path) {
                for (auto& failure : failures_) {
                    if (failure.GetPath().empty()) {
                        failure.SetPath(path);
                    } else {
                        failure.SetPath(path + "." + failure.GetPath());
                    }
                }
            }

        private:
            std::vector<Failure> failures_;
        };

        static std::optional<FailureCollection> Append(
                std::optional<FailureCollection> lhs,
                const std::optional<FailureCollection>& rhs) {
            if (lhs.has_value()) {
                if (rhs.has_value()) {
                    lhs.value().Append(rhs.value());
                    return lhs;
                } else {
                    return lhs;
                }
            } else {
                return rhs;
            }
        }

        static std::optional<FailureCollection> Append(
                std::optional<FailureCollection> lhs,
                const std::optional<Failure>& rhs) {
            if (lhs.has_value()) {
                if (rhs.has_value()) {
                    lhs.value().Append(rhs.value());
                    return lhs;
                } else {
                    return lhs;
                }
            } else if (rhs.has_value()){
                return FailureCollection(rhs.value());
            } else {
                return std::nullopt;
            }
        }
    }

    class TransformResult {
    public:
        TransformResult()
        : failure_collection_(std::nullopt) {}

        explicit TransformResult(Failure failure)
        : failure_collection_(failure) {}

        TransformResult(const std::optional<internal::FailureCollection>& failures)
                : failure_collection_(failures) {}

        bool Success() const {
            return failure_collection_.has_value() == false;
        }

        const std::vector<Failure> GetFailures() const {
            if (Success()) {
                return std::vector<Failure>();
            } else {
                return failure_collection_.value().GetFailures();
            }
        }

        void Append(const TransformResult& other) {
            failure_collection_ = internal::Append(failure_collection_, other.failure_collection_);
        }
        
        void Append(const std::optional<Failure>& failure) {
            failure_collection_ = internal::Append(failure_collection_, failure);
        }

        void AddPath(const std::string& path) {
            if (failure_collection_.has_value()) {
                failure_collection_.value().AddPath(path);
            }
        }
    private:
        std::optional<internal::FailureCollection> failure_collection_;
    };

    static bool operator== (const TransformResult& lhs, const TransformResult& rhs) {
        return lhs.GetFailures() == rhs.GetFailures();
    }

};  // rapidjson

#endif //RAPIDJSON_FAILURE_COLLECTION_H
