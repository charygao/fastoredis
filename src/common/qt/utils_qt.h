#pragma once

#include <QModelIndex>
#include <QEvent>
#include <QDesktopServices>

namespace common
{
    namespace utils_qt
    {
        template<typename Type>
        inline Type item(const QModelIndex& index)
        {
            return dynamic_cast<Type>(static_cast<Type>(index.internalPointer()));
        }

        template<typename Type>
        inline Type get_item(const QModelIndex& index,Type root)
        {
            Type result = root;
            if (index.isValid())
            {
                Type item = static_cast<Type>(index.internalPointer());
                if (item)
                    result= item;
            }
            return result;
        }

        template<typename value_t, unsigned event_t>
        class Event : public QEvent
        {
        public:
            typedef value_t value_type;
            typedef QEvent base_class;
            typedef QObject* const senders_type;
            enum { EventType = event_t };

            Event(senders_type sender, const value_t& initValue)
                : base_class((base_class::Type)EventType), _value(initValue), _sender(sender){}

            const value_t& value() const
            {
                return _value;
            }

            senders_type sender() const
            {
                return _sender;
            }

        private:
            const value_t _value;
            senders_type _sender;
        };

        template<typename error_t>
        class EventInfo
        {
        public:
            typedef error_t error_type;

            EventInfo(const error_type& er)
                : errorInfo_(er){}

            error_type errorInfo() const
            {
                return errorInfo_;
            }

            void setErrorInfo(error_type er)
            {
                errorInfo_ = er;
            }

        protected:
            error_type errorInfo_;
        };

        const QString& applicationDirPath();
    }
}
