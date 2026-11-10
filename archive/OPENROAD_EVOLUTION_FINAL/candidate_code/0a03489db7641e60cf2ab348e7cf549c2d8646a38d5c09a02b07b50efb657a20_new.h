// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.95400521;
  double density_weight = 0.18075214;
  double prefix_weight = 0.30724446;
  double neighborhood_weight = 0.03270445;
  double late_weight = 0.26799771;
  double critical_weight = 0.16949908;
  unsigned budget = 24;
  unsigned neighborhood = 12;
  unsigned spatial_mode = 0;
  bool use_dp = false;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
