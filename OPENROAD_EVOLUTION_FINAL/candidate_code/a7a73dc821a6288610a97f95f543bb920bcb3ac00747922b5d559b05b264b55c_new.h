// SPDX-License-Identifier: BSD-3-Clause
#pragma once
namespace ord::learning {
struct PolicyConfig
{
  double load_weight = 0.86538060;
  double density_weight = 0.05345844;
  double prefix_weight = 0.23756261;
  double neighborhood_weight = 0.26257903;
  double late_weight = 0.17832623;
  double critical_weight = 0.29843645;
  unsigned budget = 37;
  unsigned neighborhood = 4;
  unsigned spatial_mode = 0;
  bool use_dp = true;
};
inline constexpr PolicyConfig policyConfig() { return {}; }
}  // namespace ord::learning
